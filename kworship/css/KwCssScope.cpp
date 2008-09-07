/**
 * @file KwCssScope.cpp
 * @brief Cascading style scope.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssScope.h"
#include "KwCssStyleRule.h"
#include "KwCssStyleSheet.h"

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
    StyleSheetList::iterator it;
    for (it = m_styleSheets.begin(); it != m_styleSheets.end(); ++it)
    {
      /// @todo reference count
      delete *it;
    }
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
 * Virtual interface
 */

/// Get the type id corresponding to this type.
KwCssScopeKey::ScopeTypeId KwCssScope::getTypeId() const
{
  /// @todo optimise by caching type id
  return KwCssScopeKey::registerScopeType("scope");
}

/*
 * Accessors
 */

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

