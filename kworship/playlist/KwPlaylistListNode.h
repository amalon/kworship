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

#ifndef _KwPlaylistListNode_h_
#define _KwPlaylistListNode_h_

/**
 * @file KwPlaylistListNode.h
 * @brief A playlist node for a list.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistNode.h"

class KwPlaylistList;

/// A playlist node for a list.
class KwPlaylistListNode : public KwPlaylistNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistListNode(KwPlaylistNode* parent, KwPlaylistList* item);

    /// Destructor.
    virtual ~KwPlaylistListNode();

    /*
     * Accessors
     */

    KwPlaylistList* getItem();

    /*
     * Main interface
     */

    virtual QVariant getData(int role, int column);

    virtual int getChildCount() const;

    virtual Qt::ItemFlags getFlags(Qt::ItemFlags& defaultFlags) const;

  protected:

    virtual KwPlaylistNode* _getChild(int index);

  private:

    /*
     * Variables
     */

    /// Playlist item.
    KwPlaylistList* m_item;
};

#endif // _KwPlaylistListNode_h_

