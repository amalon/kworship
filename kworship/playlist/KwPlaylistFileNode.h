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

#ifndef _KwPlaylistFileNode_h_
#define _KwPlaylistFileNode_h_

/**
 * @file KwPlaylistFileNode.h
 * @brief A playlist node for a file.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistNode.h"

class KwPlaylistFile;

/// A playlist node for a file.
class KwPlaylistFileNode : public KwPlaylistNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistFileNode(KwPlaylistNode* parent, KwPlaylistFile* item);

    /// Destructor.
    virtual ~KwPlaylistFileNode();

    /*
     * Main interface
     */

    virtual QVariant getData(int role, int column);

    virtual void activate(KwDisplayManager* manager);

    // Reimplemented
    virtual KwPlaylistItem *playlistItem() const;

  private:

    /*
     * Variables
     */

    /// Playlist item.
    KwPlaylistFile* m_item;
};

#endif // _KwPlaylistFileNode_h_

