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

#ifndef _KwMediaPreferencesAudio_h_
#define _KwMediaPreferencesAudio_h_

/**
 * @file KwMediaPreferencesAudio.h
 * @brief A media item's audio preferences.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractMediaPreferences.h"

/// A media item's audio preferences.
/**
 * Basically this is audio preferences such as volume, muted, fadeout time.
 */
class KwMediaPreferencesAudio : public KwAbstractMediaPreferences
{
    Q_OBJECT
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwMediaPreferencesAudio();

    /// Destructor.
    virtual ~KwMediaPreferencesAudio();

    /*
     * Accessors
     */

    /// Get the volume level.
    qreal getVolume() const;

    /// Get whether the audio is muted.
    bool getMuted() const;

    /// Get the fadeout time in msecs.
    qint32 getFadeoutMsec() const;

  public slots:

    /*
     * Slots
     */

    /// Set the volume level.
    void setVolume(qreal volume);

    /// Set whether the audio is muted.
    void setMuted(bool muted);

    /// Set the fadeout time in msecs.
    void setFadeoutMsec(qint32 fadeoutMsec);

  signals:

    /*
     * Signals
     */

    /// Volume level has changed.
    void volumeChanged(qreal newVolume);

    /// Muted has changed.
    void mutedChanged(bool muted);

  private:

    /*
     * Variables
     */

    /// Volume level.
    qreal m_volume;

    /// Whether the sound is muted.
    bool m_muted;

    /// Audio fadeout time in msec.
    qint32 m_fadeoutMsec;

};

#endif // _KwMediaPreferencesAudio_h_

