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
 * @file KwSongdbNode.cpp
 * @brief A node on a song database tree.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbNode.h"
#include "KwSongdbSong.h"
#include "KwSongdbVersion.h"

#include <cassert>

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwSongdbNode::KwSongdbNode(KwSongdbNode* parent)
: DefaultModelNode(parent)
{
}

/// Destructor.
KwSongdbNode::~KwSongdbNode()
{
}

/*
 * Associated data access
 */

/// Get the song associated with this node.
KwSongdbSong* KwSongdbNode::associatedSong()
{
  if (0 != getParent())
  {
    KwSongdbNode* parent = dynamic_cast<KwSongdbNode*>(getParent());
    Q_ASSERT(0 != parent);
    KwSongdbVersion* version = parent->associatedSongVersion();
    if (0 != version)
    {
      return version->song();
    }
  }
  return 0;
}

/// Get the song version associated with this node.
KwSongdbVersion* KwSongdbNode::associatedSongVersion()
{
  if (0 != getParent())
  {
    KwSongdbNode* parent = dynamic_cast<KwSongdbNode*>(getParent());
    Q_ASSERT(parent);
    return parent->associatedSongVersion();
  }
  return 0;
}

/*
 * Drag and drop
 */

/// Get flags for this item.
Qt::ItemFlags KwSongdbNode::getFlags(Qt::ItemFlags defaultFlags) const
{
  return defaultFlags;
}

/// Get mime data string for this set of songs.
QString KwSongdbNode::mimeData()
{
  return QString();
}

