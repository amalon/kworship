/**
 * @file KwMediaPreferencesAudio.cpp
 * @brief A media item's audio preferences.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwMediaPreferencesAudio.h"

/*
 * Constructors + destructors
 */

/// Default constructor.
KwMediaPreferencesAudio::KwMediaPreferencesAudio()
: m_volume(1.0)
, m_muted(false)
, m_fadeoutMsec(0)
{
}

/// Destructor.
KwMediaPreferencesAudio::~KwMediaPreferencesAudio()
{
}

/*
 * Accessors
 */

/// Get the volume level.
KwMediaPreferencesAudio::Volume KwMediaPreferencesAudio::getVolume() const
{
  return m_volume;
}

/// Get whether the audio is muted.
bool KwMediaPreferencesAudio::getMuted() const
{
  return m_muted;
}

/// Get the fadeout time in msecs.
KwMediaPreferencesAudio::TimeInterval KwMediaPreferencesAudio::getFadeoutMsec() const
{
  return m_fadeoutMsec;
}

/*
 * Mutators
 */

/// Set the volume level.
void KwMediaPreferencesAudio::setVolume(Volume volume)
{
  m_volume = volume;
}

/// Set whether the audio is muted.
void KwMediaPreferencesAudio::setMuted(bool muted)
{
  m_muted = muted;
}

/// Set the fadeout time in msecs.
void KwMediaPreferencesAudio::setFadeoutMsec(TimeInterval fadeoutMsec)
{
  m_fadeoutMsec = fadeoutMsec;
}

