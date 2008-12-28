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

/// Import from CSS-like format into the sheet.
void KwCssStyleSheet::import(const KwCssSchema* schema, const QString& sheet)
{
  QString css = sheet;

  // Strip out comments and newlines
  static QRegExp reComment("\\/\\*([^*]|\\*[^/])*\\*\\/|\n");
  css.replace(reComment, " ");

  // Go through rules
  static QRegExp reRuleStart("^\\s*(\\S[^{]*)?\\s*\\{\\s*");
  int rulesPos = 0;
  int lastRulesPos = 0;
  while (-1 != (rulesPos = reRuleStart.indexIn(css, lastRulesPos, QRegExp::CaretAtOffset)))
  {
    lastRulesPos = rulesPos + reRuleStart.matchedLength();
    KwCssStyleRule rule;

    // Read the key criteria
    static QRegExp reCriteriaKey("^(\\w*)(#(\\w+))?\\s*");
    KwCssStyleRule::KeyList keys;
    QString head = reRuleStart.cap(1);
    int headPos = 0;
    int lastHeadPos = 0;
    while (-1 != (headPos = reCriteriaKey.indexIn(head, lastHeadPos, QRegExp::CaretAtOffset)) && reCriteriaKey.matchedLength() > 0)
    {
      lastHeadPos = headPos + reCriteriaKey.matchedLength();
      QString keyTypeName = reCriteriaKey.cap(1);
      QString keyName = reCriteriaKey.cap(2);
      int keyType = -1;
      if (!keyTypeName.isEmpty())
      {
        keyType = KwCssScopeKey::registerScopeType(keyTypeName);
      }
      keys += KwCssScopeKey(keyType, keyName);
    }
    rule.setCriteriaKeys(keys);

    // Read the class criteria
    static QRegExp reCriteriaClass("^\\.(\\w+)\\s*");
    KwCssStyleRule::StringSet classes;
    while (-1 != (headPos = reCriteriaClass.indexIn(head, lastHeadPos, QRegExp::CaretAtOffset)))
    {
      lastHeadPos = headPos + reCriteriaClass.matchedLength();
      classes += reCriteriaClass.cap(1);
    }
    rule.setCriteriaClasses(classes);

    // Read the class includes
    static QRegExp reIncludeStart("^:\\s*");
    if (-1 != (headPos = reIncludeStart.indexIn(head, lastHeadPos, QRegExp::CaretAtOffset)))
    {
      lastHeadPos = headPos + reIncludeStart.matchedLength();
      KwCssStyleRule::StringSet classes;
      while (-1 != (headPos = reCriteriaClass.indexIn(head, lastHeadPos, QRegExp::CaretAtOffset)))
      {
        lastHeadPos = headPos + reCriteriaClass.matchedLength();
        classes += reCriteriaClass.cap(1);
      }
      rule.setIncludedStyles(classes);
    }

    // Should be no more head left
    static QRegExp reWhitespace("^\\s*$");
    if (-1 == reWhitespace.indexIn(head, lastHeadPos, QRegExp::CaretAtOffset))
    {
      Q_ASSERT(0&& "Expected '{' near something else");
    }

    // Read the styles
    lastRulesPos = rule.getStyles()->import(schema, css, lastRulesPos);

    // End of rule
    static QRegExp reRuleEnd("^\\}\\s*");
    if (-1 != (rulesPos = reRuleEnd.indexIn(css, lastRulesPos, QRegExp::CaretAtOffset)))
    {
      lastRulesPos = rulesPos + reRuleEnd.matchedLength();
    }
    else
    {
      // Expected end of rule but got something else
      Q_ASSERT(0&& "Expected '}' near something else");
    }
    m_rules += rule;
  }
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

/// Convert to CSS-like format.
QString KwCssStyleSheet::toString() const
{
  /// @todo Take into account of shared styles in rules!
  QString result = "/* Doesn't take shared styles into account */\n";
  foreach (const KwCssStyleRule& rule, m_rules)
  {
    result += rule.toString();
  }
  return result;
}
