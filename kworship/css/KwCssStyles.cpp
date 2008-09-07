/**
 * @file KwCssStyles.cpp
 * @brief Set of cascading style properties.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssStyles.h"
#include "KwCssStyleStates.h"
#include "KwCssAbstractStyle.h"
#include "KwCssAbstractStyleState.h"

/*
 * Constructors + destructors
 */

/// Default constructor.
KwCssStyles::KwCssStyles()
: m_styles()
{
}

/// Copy constructor.
KwCssStyles::KwCssStyles(const KwCssStyles& other)
: m_styles()
{
  StyleDictionary::const_iterator it;
  for (it = other.m_styles.begin(); it != other.m_styles.end(); ++it)
  {
    m_styles[it.key()] = (*it)->duplicate();
  }
}

/// Destructor.
KwCssStyles::~KwCssStyles()
{
  StyleDictionary::iterator it;
  for (it = m_styles.begin(); it != m_styles.end(); ++it)
  {
    delete *it;
  }
}

/*
 * Main interface
 */

/// Set a style.
void KwCssStyles::setRawStyle(QString name, KwCssAbstractStyle* style)
{
  // Delete previous value
  StyleDictionary::iterator it = m_styles.find(name);
  if (it != m_styles.end())
  {
    delete *it;
  }
  // Set new value
  m_styles[name] = style;
}

/*
 * Operators
 */

/// Apply styles.
KwCssStyleStates& operator << (KwCssStyleStates& states, const KwCssStyles& styles)
{
  // go through styles, adjusting the states
  KwCssStyles::StyleDictionary::const_iterator it;
  for (it = styles.m_styles.begin(); it != styles.m_styles.end(); ++it)
  {
    KwCssAbstractStyleState*& state = states[it.key()];
    if (0 == state)
    {
      state = (*it)->getNewState();
    }
    (*state) << (*it);
  }
  return states;
}

