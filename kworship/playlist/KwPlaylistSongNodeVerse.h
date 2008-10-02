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

#ifndef _KwPlaylistSongNodeVerse_h_
#define _KwPlaylistSongNodeVerse_h_

/**
 * @file KwPlaylistSongNodeVerse.h
 * @brief A playlist node for a song verse.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistNode.h"

class KwPlaylistSong;

/// A playlist node for a song verse.
class KwPlaylistSongNodeVerse : public KwPlaylistNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistSongNodeVerse(KwPlaylistNode* parent, KwPlaylistSong* item, int verse);

    /// Destructor.
    virtual ~KwPlaylistSongNodeVerse();

    /*
     * Main interface
     */

    virtual QVariant getData(int role, int column);

    virtual void activate(KwDisplayManager* manager);

  private:

    /*
     * Variables
     */

    /// Playlist item.
    KwPlaylistSong* m_item;

    /// Verse number.
    int m_verse;
};

#endif // _KwPlaylistSongNodeVerse_h_

