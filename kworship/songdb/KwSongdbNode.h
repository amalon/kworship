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

#ifndef _KwSongdbNode_h_
#define _KwSongdbNode_h_

/**
 * @file KwSongdbNode.h
 * @brief A node on a song database tree.
 * @author James Hogan <james@albanarts.com>
 */

#include "NodeBasedModel.h"

class KwDisplayManager;
class KwSongdbSong;
class KwSongdbVersion;

/// A node on a song database tree.
/**
 * Inherit from this class for each song database node type.
 */
class KwSongdbNode : public DefaultModelNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwSongdbNode(KwSongdbNode* parent);

    /// Destructor.
    virtual ~KwSongdbNode();

    /*
     * Associated data access
     */

    /// Get the song associated with this node.
    virtual KwSongdbSong* associatedSong();

    /// Get the song version associated with this node.
    virtual KwSongdbVersion* associatedSongVersion();

    /*
     * Drag and drop
     */

    /// Get flags for this item.
    virtual Qt::ItemFlags getFlags(Qt::ItemFlags defaultFlags) const;

    /// Get mime data string for this set of songs.
    virtual QString mimeData();
};

#endif // _KwSongdbNode_h_

