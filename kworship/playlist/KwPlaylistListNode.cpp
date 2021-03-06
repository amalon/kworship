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
 * @file KwPlaylistListNode.cpp
 * @brief A playlist node for a list.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistListNode.h"
#include "KwPlaylistList.h"

#include <KIcon>

#include <cassert>

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistListNode::KwPlaylistListNode(KwPlaylistNode* parent, KwPlaylistList* item)
: KwPlaylistNode(parent)
, m_item(item)
{
}

/// Destructor.
KwPlaylistListNode::~KwPlaylistListNode()
{
}

/*
 * Accessors
 */

KwPlaylistList* KwPlaylistListNode::getItem()
{
  return m_item;
}

/*
 * Main interface
 */

QVariant KwPlaylistListNode::getData(int role, int column)
{
  if (role == Qt::DisplayRole)
  {
    if (column == 0)
    {
      return "List";
    }
  }
  else if (role == Qt::DecorationRole)
  {
    if (column == 0)
    {
      return KIcon("playlist");
    }
  }
  return QVariant();
}

int KwPlaylistListNode::getChildCount() const
{
  return m_item->getItemCount();
}

Qt::ItemFlags KwPlaylistListNode::getFlags(Qt::ItemFlags& defaultFlags) const
{
  return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
}

KwPlaylistItem *KwPlaylistListNode::playlistItem() const
{
  return m_item;
}

KwPlaylistNode* KwPlaylistListNode::_getChild(int index)
{
  KwPlaylistItem* item = m_item->getItem(index);
  assert(item != 0);
  return item->getNode(this);
}

