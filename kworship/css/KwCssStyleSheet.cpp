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
 * @file KwCssStyleSheet.cpp
 * @brief Cascading style sheet.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssStyleSheet.h"
#include "KwCssStyleRule.h"

#include <cassert>

/*
 * Constructors + destructors
 */

/// Default constructor.
KwCssStyleSheet::KwCssStyleSheet()
: m_rules()
{
}

/// Copy constructor.
/**
 * This copies all except the actual styles in each rule which are aliased.
 */
KwCssStyleSheet::KwCssStyleSheet(const KwCssStyleSheet& copy)
: m_rules()
{
  /// @todo Copy rules
  assert(0&&"unimplemented");
}

/// Destructor.
KwCssStyleSheet::~KwCssStyleSheet()
{
}

/*
 * Main interface
 */

/// Clear the rules.
void KwCssStyleSheet::clear()
{
  m_rules.clear();
}

/// Append a rule.
void KwCssStyleSheet::addRule(const KwCssStyleRule& rule)
{
  m_rules.push_back(rule);
}

/// Import another stylesheet.
void KwCssStyleSheet::importStyleSheet(const KwCssStyleSheet* styleSheet)
{
  m_rules += styleSheet->m_rules;
}

/*
 * Accessors
 */

/// Get the rules.
KwCssStyleSheet::RuleList& KwCssStyleSheet::getRules()
{
  return m_rules;
}

/// Get the constant rules.
const KwCssStyleSheet::RuleList& KwCssStyleSheet::getRules() const
{
  return m_rules;
}
