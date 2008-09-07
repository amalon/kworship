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
