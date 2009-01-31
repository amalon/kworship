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

#ifndef _KwPlaylistNode_h_
#define _KwPlaylistNode_h_

/**
 * @file KwPlaylistNode.h
 * @brief A node on a playlist tree.
 * @author James Hogan <james@albanarts.com>
 */

#include "NodeBasedModel.h"

#include <kdemacros.h>

class KwDisplayManager;

/// A node on a playlist tree.
/**
 * Inherit from this class for each playlist node type.
 */
class KDE_EXPORT KwPlaylistNode : public DefaultModelNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistNode(KwPlaylistNode* parent);

    /// Destructor.
    virtual ~KwPlaylistNode();

    /*
     * Main interface
     */

    /// Get the flags for this node.
    virtual Qt::ItemFlags getFlags(Qt::ItemFlags& defaultFlags) const;

    /// Activate the node using a display manager.
    virtual void activate(KwDisplayManager* manager);

};

#endif // _KwPlaylistNode_h_

