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
qreal KwMediaPreferencesAudio::getVolume() const
{
  return m_volume;
}

/// Get whether the audio is muted.
bool KwMediaPreferencesAudio::getMuted() const
{
  return m_muted;
}

/// Get the fadeout time in msecs.
qint32 KwMediaPreferencesAudio::getFadeoutMsec() const
{
  return m_fadeoutMsec;
}

/*
 * Slots
 */

/// Set the volume level.
void KwMediaPreferencesAudio::setVolume(qreal volume)
{
  m_volume = volume;
  volumeChanged(volume);
}

/// Set whether the audio is muted.
void KwMediaPreferencesAudio::setMuted(bool muted)
{
  m_muted = muted;
  mutedChanged(muted);
}

/// Set the fadeout time in msecs.
void KwMediaPreferencesAudio::setFadeoutMsec(qint32 fadeoutMsec)
{
  m_fadeoutMsec = fadeoutMsec;
}

