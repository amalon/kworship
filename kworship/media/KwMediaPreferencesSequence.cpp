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
 * @file KwMediaPreferencesSequence.cpp
 * @brief A media item's sequence preferences.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwMediaPreferencesSequence.h"

/*
 * Constructors + destructors
 */

/// Default constructor.
KwMediaPreferencesSequence::KwMediaPreferencesSequence()
: m_startMsec(0)
, m_endMsec(-1)
{
}

/// Destructor.
KwMediaPreferencesSequence::~KwMediaPreferencesSequence()
{
}

/*
 * Accessors
 */

/// Has the sequence got an end?
bool KwMediaPreferencesSequence::hasEnd() const
{
  return m_endMsec != -1;
}

/// Get the start time in msecs.
KwMediaPreferencesSequence::Clock KwMediaPreferencesSequence::getStartMsec() const
{
  return m_startMsec;
}

/// Get the end time in msecs.
KwMediaPreferencesSequence::Clock KwMediaPreferencesSequence::getEndMsec() const
{
  return m_endMsec;
}

/// Get the length in msecs.
KwMediaPreferencesSequence::Clock KwMediaPreferencesSequence::getLengthMsec() const
{
  return m_endMsec - m_startMsec;
}

/*
 * Mutators
 */

/// Set the start time in msecs.
void KwMediaPreferencesSequence::setStartMsec(Clock startMsec, bool moveEnd)
{
  if (moveEnd && hasEnd())
  {
    m_endMsec += (startMsec - m_startMsec);
  }
  m_startMsec = startMsec;
}

/// Set the end time in msecs.
void KwMediaPreferencesSequence::setEndMsec(Clock endMsec)
{
  m_endMsec = endMsec;
}

/// Set the length in msecs.
void KwMediaPreferencesSequence::setLengthMsec(Clock lengthMsec)
{
  m_endMsec = m_startMsec + lengthMsec;
}


