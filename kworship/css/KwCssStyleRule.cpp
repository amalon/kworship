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

/// Set the set of required classes.
void KwCssStyleRule::setCriteriaClasses(const StringSet& classes)
{
  m_criteriaClasses = classes;
}

/// Set a style.
void KwCssStyleRule::setRawStyle(QString name, KwCssAbstractStyle* style)
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
const ReferenceCountedExtension<KwCssStyles>* KwCssStyleRule::getStyles() const
{
  return m_styles;
}

