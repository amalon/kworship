/**
 * @file KwCssStyleStates.h
 * @brief Set of cascading style property states.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssStyleStates.h"
#include "KwCssStyles.h"
#include "KwCssAbstractStyleState.h"

/*
 * Constructors + destructors
 */

/// Default constructor.
KwCssStyleStates::KwCssStyleStates()
: m_styleStates()
{
}

/// Copy constructor.
KwCssStyleStates::KwCssStyleStates(const KwCssStyleStates& other)
: m_styleStates()
{
  // Use the duplicate function
  StyleStateDictionary::const_iterator it;
  for (it = other.m_styleStates.begin(); it != other.m_styleStates.end(); ++it)
  {
    m_styleStates[it.key()] = (*it)->duplicate();
  }
}

/// Destructor.
KwCssStyleStates::~KwCssStyleStates()
{
  StyleStateDictionary::iterator it;
  for (it = m_styleStates.begin(); it != m_styleStates.end(); ++it)
  {
    delete *it;
  }
}

/*
 * Main interface
 */

/// Clear all states.
void KwCssStyleStates::clear()
{
  // First clean up
  StyleStateDictionary::iterator it;
  for (it = m_styleStates.begin(); it != m_styleStates.end(); ++it)
  {
    delete *it;
  }
  m_styleStates.clear();
}

/// Get a state.
const KwCssAbstractStyleState* KwCssStyleStates::getRawStyle(QString name) const
{
  StyleStateDictionary::const_iterator it = m_styleStates.find(name);
  if (it != m_styleStates.end())
  {
    return *it;
  }
  else
  {
    return 0;
  }
}

/*
 * Operators
 */

/// Copy assignment operator.
KwCssStyleStates& KwCssStyleStates::operator = (const KwCssStyleStates& other)
{
  clear();

  // Use the duplicate function
  StyleStateDictionary::const_iterator it;
  for (it = other.m_styleStates.begin(); it != other.m_styleStates.end(); ++it)
  {
    m_styleStates[it.key()] = (*it)->duplicate();
  }

  return *this;
}

/// Index into styles mapping.
KwCssAbstractStyleState*& KwCssStyleStates::operator [] (QString name)
{
  return m_styleStates[name];
}

