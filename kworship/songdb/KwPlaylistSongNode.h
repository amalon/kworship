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

#ifndef _KwPlaylistSongNode_h_
#define _KwPlaylistSongNode_h_

/**
 * @file KwPlaylistSongNode.h
 * @brief A playlist node for a song.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistNode.h"

class KwPlaylistSong;

/// A playlist node for a song.
class KwPlaylistSongNode : public KwPlaylistNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistSongNode(KwPlaylistNode* parent, KwPlaylistSong* item);

    /// Destructor.
    virtual ~KwPlaylistSongNode();

    /*
     * Main interface
     */

    virtual QVariant getData(int role, int column);

    virtual int getChildCount() const;

    // Reimplemented
    virtual KwPlaylistItem *playlistItem() const;

  protected:

    virtual KwPlaylistNode* _getChild(int index);

  private:

    /*
     * Variables
     */

    /// Playlist item.
    KwPlaylistSong* m_item;
};

#endif // _KwPlaylistSongNode_h_

