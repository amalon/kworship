/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   KWorship is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   KWorship is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with KWorship.  If not, see <http://www.gnu.org/licenses/>.     *
 ***************************************************************************/

#ifndef _KwMediaItem_h_
#define _KwMediaItem_h_

/**
 * @file KwMediaItem.h
 * @brief A media item.
 * @author James Hogan <james@albanarts.com>
 */

#include <QUrl>

class KwMediaManager;
class KwMediaPreferencesSequence;
class KwMediaPreferencesAudio;
class KwMediaPreferencesVisual;

/// A media item.
class KwMediaItem
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwMediaItem(const QUrl& url);

    /// Destructor.
    virtual ~KwMediaItem();

    /*
     * Main interface
     */

    /// Start playing the media through a media manager.
    void playMedia(KwMediaManager* mediaManager);

    /// Enable sequence.
    void setSequence(bool enabled);

    /// Enable audio.
    void setAudio(bool enabled);

    /// Enable video.
    void setVideo(bool enabled);

    /*
     * Accessors
     */

    /// Get the url of the file.
    QUrl getUrl() const;

  private:

    /*
     * Variables
     */

    /// Url.
    QUrl m_url;

    /// Sequence preferences.
    KwMediaPreferencesSequence* m_sequencePreferences;

    /// Audio preferences.
    KwMediaPreferencesAudio* m_audioPreferences;

    /// Visual preferences.
    KwMediaPreferencesVisual* m_visualPreferences;
};

#endif // _KwMediaItem_h_

