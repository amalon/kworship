/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   KWorship is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   KWorship is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with KWorship.  If not, write to the Free Software Foundation,  *
 *   Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.   *
 ***************************************************************************/

/**
 * @file KwCssScope.cpp
 * @brief Cascading style scope.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssScope.h"
#include "KwCssStyleRule.h"
#include "KwCssStyleSheet.h"

#include <QDomDocument>
#include <QDomElement>

/*
 * Constructors + destructors
 */

/// Primary constructor.
KwCssScope::KwCssScope(KwCssScope* parent)
: m_parentScope(parent)
, m_childScopes()
, m_name()
, m_classes()
, m_styleSheets()
, m_styles()
{
  if (0 != m_parentScope)
  {
    parent->m_childScopes.insert(this);
  }
}

/// Destructor.
KwCssScope::~KwCssScope()
{
  // Remove from parent's child list.
  if (0 != m_parentScope)
  {
    m_parentScope->m_childScopes.remove(this);
  }

  // Remove from children and recalculate styles.
  {
    ScopeSet::iterator it;
    for (it = m_childScopes.begin(); it != m_childScopes.end(); ++it)
    {
      (*it)->m_parentScope = 0;
      (*it)->recalculateStyles();
    }
  }

  // Clean style sheets
  {
    foreach (KwCssStyleSheet* stylesheet, m_styleSheets)
    {
      /// @todo reference count
      delete stylesheet;
    }
  }
}

/*
 * DOM filters
 */

/// Import the style information from a DOM.
void KwCssScope::importStylesFromDom(const QDomElement& element, KwResourceManager* resourceManager)
{
  // Classes
  QDomNodeList elems = element.elementsByTagName("class");
  for (int i = 0; i < elems.count(); ++i)
  {
    m_classes += elems.at(i).toElement().text();
  }

  // Stylesheets
  elems = element.elementsByTagName("sheet");
  for (int i = 0; i < elems.count(); ++i)
  {
    KwCssStyleSheet* newSheet = new KwCssStyleSheet;
    newSheet->import(elems.at(i).toElement().text());
    m_styleSheets.push_back(newSheet);
  }
  if (elems.count() > 0)
  {
    recalculateStyles();
  }

  // Explicit styles
  elems = element.elementsByTagName("explicit");
  for (int i = 0; i < elems.count(); ++i)
  {
    m_styles.import(elems.at(i).toElement().text());
  }
}

/// Export the style information to a DOM.
void KwCssScope::exportStylesToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const
{
  // Start with the classes
  foreach (QString className, m_classes)
  {
    QDomElement classElem = document.createElement("class");
    element.appendChild(classElem);
    classElem.appendChild(document.createTextNode(className));
  }

  // Now for the stylesheets
  foreach (KwCssStyleSheet* stylesheet, m_styleSheets)
  {
    QDomElement sheetElem = document.createElement("sheet");
    element.appendChild(sheetElem);
    sheetElem.appendChild(document.createTextNode(stylesheet->toString()));
  }

  // And finally the explicit styles
  if (!m_styles.isEmpty())
  {
    QDomElement explicitElem = document.createElement("explicit");
    element.appendChild(explicitElem);
    explicitElem.appendChild(document.createTextNode(m_styles.toString()));
  }
}

/*
 * Main interface
 */

/// Add a stylesheet for this scope.
void KwCssScope::addStyleSheet(KwCssStyleSheet* styleSheet)
{
  m_styleSheets.push_back(styleSheet);
  recalculateStyles();
}

/// Add a class to this scope.
void KwCssScope::addClass(QString className)
{
  m_classes += className;
  recalculateStyles();
}

/// Get all the styles included in this scope.
const KwCssStyleStates& KwCssScope::getStyles() const
{
  return m_cachedStyles;
}

/// Recalculate all styles.
void KwCssScope::recalculateStyles()
{
  /*
   * cached styles
   * unmatched rules stylesheet
   *
   * get parent styles
   * add classes
   * get parent unmatched style rules
   * go through stylesheets
   *  apply any rules that match in order, removing as we go from local list
   * apply explicit styles
   */
  // Get the base styles from the parent
  if (0 != m_parentScope)
  {
    m_cachedStyles = m_parentScope->getStyles();
    m_cachedStyleSheet = m_parentScope->m_cachedStyleSheet;
    m_cachedClasses = m_parentScope->m_cachedClasses;
  }
  else
  {
    m_cachedStyles.clear();
    m_cachedStyleSheet.clear();
  }
  // Add local stylesheets
  {
    StyleSheetList::iterator it;
    for (it = m_styleSheets.begin(); it != m_styleSheets.end(); ++it)
    {
      m_cachedStyleSheet.importStyleSheet(*it);
    }
  }
  // Add local classes
  m_cachedClasses += m_classes;

  // process rules
  bool processRules;
  do
  {
    processRules = false;
    QSet<QString> triggerableClasses;
    KwCssStyleSheet::Iterator it;
    for (it = m_cachedStyleSheet.getRules().begin(); it != m_cachedStyleSheet.getRules().end();)
    {
      // Match the keys
      KwCssStyleRule::KeyList& keys = (*it).getCriteriaKeys();
      if (!keys.empty() && isKeyMatching(keys.first()))
      {
        keys.pop_front();
      }
      // Match the classes
      KwCssStyleRule::StringSet& classes = (*it).getCriteriaClasses();
      classes -= m_cachedClasses;

      if (!classes.empty())
      {
        triggerableClasses += classes;
        ++it;
      }
      else if (keys.empty())
      {
        // Nothing left to match, we can apply this style and remove it from the list
        m_cachedStyles << *(*it).getStyles();
        QSet<QString> classesToApply = (*it).getIncludedStyles() - m_cachedClasses;
        if (!classesToApply.empty())
        {
          m_cachedClasses += classesToApply;
          QSet<QString> classesToTrigger = triggerableClasses & classesToApply;
          if (!classesToTrigger.empty())
          {
            triggerableClasses -= classesToTrigger;
            processRules = true;
          }
        }
        // Remove from stylesheet since it's now applied
        KwCssStyleSheet::Iterator cur = it;
        ++it;
        m_cachedStyleSheet.getRules().erase(cur);
      }
      else
      {
        ++it;
      }
    }
  }
  while (processRules);

  // Apply each style
  m_cachedStyles << m_styles;

  // Recurse to children
  {
    ScopeSet::iterator it;
    for (it = m_childScopes.begin(); it != m_childScopes.end(); ++it)
    {
      (*it)->recalculateStyles();
    }
  }
}

/*
 * Accessors
 */

/// Find whether the scope is effectively empty.
bool KwCssScope::isScopeEmpty() const
{
  return m_classes.isEmpty() && m_styleSheets.isEmpty() && m_styles.isEmpty();
}

/// Get explicit styles.
const KwCssStyles& KwCssScope::getExplicitStyles() const
{
  return m_styles;
}

/// Get the scope's key.
KwCssScopeKey KwCssScope::getKey() const
{
  return KwCssScopeKey(getTypeId(), m_name);
}

/// Find whether a scope key matches this scope.
bool KwCssScope::isKeyMatching(KwCssScopeKey key) const
{
  return (!key.isTypeSpecified() || key.getTypeId() == getTypeId())
      && (!key.isNameSpecified() || key.getName()   == m_name);
}

/*
 * Mutators
 */

/// Set the parent scope.
void KwCssScope::setParentScope(KwCssScope* parent)
{
  if (0 != m_parentScope)
  {
    m_parentScope->m_childScopes.remove(this);
  }
  m_parentScope = parent;
  if (0 != parent)
  {
    m_parentScope->m_childScopes.insert(this);
  }
  recalculateStyles();
}

