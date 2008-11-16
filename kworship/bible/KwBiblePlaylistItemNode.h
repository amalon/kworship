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

#ifndef _KwBiblePlaylistItemNode_h_
#define _KwBiblePlaylistItemNode_h_

/**
 * @file KwBiblePlaylistItemNode.h
 * @brief A playlist node for a bible passage item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistNode.h"

class KwBiblePlaylistItem;

/// A playlist node for a text.
class KwBiblePlaylistItemNode : public KwPlaylistNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwBiblePlaylistItemNode(KwPlaylistNode* parent, KwBiblePlaylistItem* item);

    /// Destructor.
    virtual ~KwBiblePlaylistItemNode();

    /*
     * Main interface
     */

    // Reimplemented
    virtual QVariant getData(int role, int column);

  private:

    /*
     * Variables
     */

    /// Playlist item.
    KwBiblePlaylistItem* m_item;
};

#endif // _KwBiblePlaylistItemNode_h_

