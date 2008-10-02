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

