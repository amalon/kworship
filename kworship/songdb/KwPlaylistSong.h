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

#ifndef _KwPlaylistSong_h_
#define _KwPlaylistSong_h_

/**
 * @file KwPlaylistSong.h
 * @brief A song playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistItem.h"
#include "KwSongdbLyricsLayout.h"

#include <kdemacros.h>

class KwSongdbVersion;

/// A song playlist item.
class KDE_EXPORT KwPlaylistSong : public KwPlaylistItem
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistSong(KwSongdbVersion* version, bool owned = false);

    /// Destructor.
    virtual ~KwPlaylistSong();

    /*
     * Accessors
     */

    /// Get the song version object.
    KwSongdbVersion* getSongVersion() const;

    /// Get the lyrics layout.
    KwSongdbLyricsLayout& getLyricsLayout();

    /*
     * DOM Translation.
     */

    virtual QString itemType() const;
    virtual void exportDetailsToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const;

    /*
     * Main interface
     */

    virtual KwPlaylistNode* getNode(KwPlaylistNode* parent);

  private:
    
    /*
     * Variables
     */

    /// Whether the version is owned or part of a database.
    bool m_owned;

    /// Song version.
    KwSongdbVersion* m_version;

    /// Lyrics layout.
    KwSongdbLyricsLayout m_lyricsLayout;
};

#endif // _KwPlaylistSong_h_

