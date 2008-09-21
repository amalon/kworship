/***************************************************************************
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   This file is part of KWorship.                                        *
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
 * @file KwPlaylistList.cpp
 * @brief A list of playlist items.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistList.h"
#include "KwPlaylistListNode.h"

#include <cassert>

/*
 * Constructors + destructor.
 */

/// Default constructor.
KwPlaylistList::KwPlaylistList()
: KwPlaylistItem()
, m_playlist()
{
}

/// Destructor.
KwPlaylistList::~KwPlaylistList()
{
}

/*
 * Child management.
 */

/// Add a child.
void KwPlaylistList::addItem(KwPlaylistItem* item, int position)
{
  if (position == -1)
  {
    m_playlist.push_back(item);
  }
  else
  {
    m_playlist.insert(position, item);
  }
  item->setParentScope(this);
}

/// Get the number of children.
int KwPlaylistList::getItemCount() const
{
  return m_playlist.size();
}

/// Get a specific child.
KwPlaylistItem* KwPlaylistList::getItem(int index)
{
  assert(index < getItemCount());
  Playlist::iterator it = m_playlist.begin();
  while (index && it != m_playlist.end())
  {
    ++it;
    --index;
  }
  assert(it != m_playlist.end());
  if (it == m_playlist.end())
  {
    return 0;
  }
  else
  {
    return *it;
  }
}

/*
 * Main interface.
 */

KwPlaylistNode* KwPlaylistList::getNode(KwPlaylistNode* parent)
{
  return new KwPlaylistListNode(parent, this);
}

