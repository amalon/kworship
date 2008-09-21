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

/**
 * @file KwPlaylistSongNode.cpp
 * @brief A playlist node for a song.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistSongNode.h"
#include "KwPlaylistSongNodeVerse.h"
#include "KwPlaylistSong.h"
#include "KwSongdbVersion.h"
#include "KwSongdbSong.h"

#include <KIcon>

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistSongNode::KwPlaylistSongNode(KwPlaylistNode* parent, KwPlaylistSong* item)
: KwPlaylistNode(parent)
, m_item(item)
{
}

/// Destructor.
KwPlaylistSongNode::~KwPlaylistSongNode()
{
}

/*
 * Main interface
 */

QVariant KwPlaylistSongNode::getData(int role, int column)
{
  if (role == Qt::DisplayRole)
  {
    if (column == 0)
    {
      return m_item->getSongVersion()->getSong()->getName();
    }
  }
  else if (role == Qt::DecorationRole)
  {
    if (column == 0)
    {
      return KIcon("song");
    }
  }
  return QVariant();
}

int KwPlaylistSongNode::getChildCount() const
{
  return m_item->getSongVersion()->getNumLyricsOrders();
}

KwPlaylistNode* KwPlaylistSongNode::_getChild(int index)
{
  return new KwPlaylistSongNodeVerse(this, m_item, index);
}

