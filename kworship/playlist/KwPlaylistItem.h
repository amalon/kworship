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

#ifndef _KwPlaylistItem_h_
#define _KwPlaylistItem_h_

/**
 * @file KwPlaylistItem.h
 * @brief An item that can be added to a playlist.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssScope.h"

class KwPlaylistNode;

/// An item that can be added to a playlist.
/**
 * Inherit from this class for each playlist item type.
 */
class KwPlaylistItem : public KwCssScope
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Default constructor.
    KwPlaylistItem();

    /// Destructor.
    virtual ~KwPlaylistItem();

    /*
     * Main interface.
     */

    /// Get a tree node for this item.
    virtual KwPlaylistNode* getNode(KwPlaylistNode* parent) = 0;
};

#endif // _KwPlaylistItem_h_

