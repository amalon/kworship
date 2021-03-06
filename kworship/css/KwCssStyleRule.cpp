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
 * @file KwCssStyleRule.cpp
 * @brief Class of cascading styles.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssStyleRule.h"

/*
 * Constructors + destructors
 */

/// Default constructor.
KwCssStyleRule::KwCssStyleRule()
: m_criteriaKeys()
, m_criteriaClasses()
, m_includedStyles()
, m_styles(new ReferenceCountedExtension<KwCssStyles>)
{
}

/// Destructor.
KwCssStyleRule::~KwCssStyleRule()
{
}

/*
 * Main interface.
 */

/// Set the set of critieria keys.
void KwCssStyleRule::setCriteriaKeys(const KeyList& keys)
{
  m_criteriaKeys = keys;
}

/// Set the set of required classes.
void KwCssStyleRule::setCriteriaClasses(const StringSet& classes)
{
  m_criteriaClasses = classes;
}

/// Set the set of included classes.
void KwCssStyleRule::setIncludedStyles(const StringSet& includes)
{
  m_includedStyles = includes;
}

/// Set a style.
void KwCssStyleRule::setRawStyle(const QString& name, KwCssAbstractStyle* style)
{
  m_styles->setRawStyle(name, style);
}

/*
 * Accessors
 */

/// Get the list of criteria keys.
KwCssStyleRule::KeyList& KwCssStyleRule::getCriteriaKeys()
{
  return m_criteriaKeys;
}

/// Get the set of criteria classes.
KwCssStyleRule::StringSet& KwCssStyleRule::getCriteriaClasses()
{
  return m_criteriaClasses;
}

/// Get the list of included styles.
const KwCssStyleRule::StringSet& KwCssStyleRule::getIncludedStyles() const
{
  return m_includedStyles;
}

/// Get the styles.
ReferenceCountedExtension<KwCssStyles>* KwCssStyleRule::getStyles() const
{
  return m_styles;
}

/// Convert to CSS-like format.
QString KwCssStyleRule::toString() const
{
  QString result;
  /// @todo Share styles among multiple rules
  foreach (const KwCssScopeKey& key, m_criteriaKeys)
  {
    if (key.isTypeSpecified())
    {
      result += key.getTypeName();
    }
    if (key.isNameSpecified())
    {
      result += "#" + key.getName();
    }
    result += " ";
  }
  foreach (const QString& className, m_criteriaClasses)
  {
    result += QString(".%1 ").arg(className);
  }
  if (!m_includedStyles.isEmpty())
  {
    result += ": ";
    foreach (const QString& className, m_includedStyles)
    {
      result += QString(".%1 ").arg(className);
    }
  }
  result += "{\n";
  result += m_styles->toString();
  result += "}\n";
  return result;
}
