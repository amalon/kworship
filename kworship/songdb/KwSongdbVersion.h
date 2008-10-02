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

#ifndef _KwSongdbVersion_h_
#define _KwSongdbVersion_h_

/**
 * @file KwSongdbVersion.h
 * @brief A song version from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include <QHash>
#include <QVector>

class KwSongdbSong;
class KwSongdbLyrics;
class KwSongdbLyricsOrder;

/// A song version from the database.
class KwSongdbVersion
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwSongdbVersion(int id);

    /// Destructor.
    virtual ~KwSongdbVersion();

    /*
     * Accessors
     */

    /// Get the song this is a version of.
    KwSongdbSong* getSong();

    /// Get lyrics by id.
    KwSongdbLyrics* getLyricsById(int id);

    /// Get lyrics by order.
    KwSongdbLyrics* getLyricsByOrder(int order);

    /// Get number of lyric verses.
    int getNumLyricsOrders();

    /// Get a lyrics order object.
    KwSongdbLyricsOrder* getLyricsOrderByOrder(int order);

    /// Get an ordered vector of lyrics.
    QVector<KwSongdbLyrics*> getOrderedLyrics();

  private:

    /*
     * Variables
     */

    /// Version id.
    int m_id;

    /// Song object.
    KwSongdbSong* m_song;

    /// Whether lyrics have been loaded.
    bool m_lyricsLoaded;

    /// Song lyrics.
    typedef QHash<int, KwSongdbLyrics*> LyricsIndex;
    LyricsIndex m_lyricsById;

    /// Lyrics ordering.
    typedef QVector<KwSongdbLyricsOrder*> LyricsOrderIndex;
    LyricsOrderIndex m_lyricsOrdersByOrder;

    /*
     * Helper functions
     */

    /// Ensure that lyrics are loaded.
    void loadLyrics();
};

#endif // _KwSongdbVersion_h_

