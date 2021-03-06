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

/**
 * @file KwPlaylistNode.cpp
 * @brief A node on a playlist tree.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistNode.h"

#include <cassert>

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistNode::KwPlaylistNode(KwPlaylistNode* parent)
: DefaultModelNode(parent)
{
}

/// Destructor.
KwPlaylistNode::~KwPlaylistNode()
{
}

/*
 * Main interface
 */

/// Get the flags for this node.
Qt::ItemFlags KwPlaylistNode::getFlags(Qt::ItemFlags& defaultFlags) const
{
  return Qt::ItemIsDragEnabled | defaultFlags;
}

/// Activate the node using a display manager.
void KwPlaylistNode::activate(KwDisplayManager*)
{
}

KwPlaylistItem *KwPlaylistNode::playlistItem() const
{
  return 0;
}
