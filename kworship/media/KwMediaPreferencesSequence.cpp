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


