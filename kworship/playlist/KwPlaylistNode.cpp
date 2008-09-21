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
: m_parent(parent)
{
}

/// Destructor.
KwPlaylistNode::~KwPlaylistNode()
{
}

/*
 * Main interface
 */

/// Get the parent.
KwPlaylistNode* KwPlaylistNode::getParent()
{
  return m_parent;
}

/// Get data associated with the node.
QVariant KwPlaylistNode::getData(int role, int column)
{
  Q_UNUSED(role)
  Q_UNUSED(column)
  return QVariant();
}

/// Get the number of children.
int KwPlaylistNode::getChildCount() const
{
  return 0;
}

/// Get a child node by index.
KwPlaylistNode* KwPlaylistNode::getChild(int index)
{
  assert(index < getChildCount());
  if (index >= m_children.size())
  {
    int prevSize = m_children.size();
    int newSize = getChildCount();
    m_children.resize(newSize);
    for (int i = prevSize; i < newSize; ++i)
    {
      m_children[i] = 0;
    }
  }
  if (0 == m_children[index])
  {
    m_children[index] = _getChild(index);
  }
  return m_children[index];
}

/// Clear the cache of child nodes.
void KwPlaylistNode::clearChildCache()
{
  m_children.clear();
}

/// Get the index of a certain child.
int KwPlaylistNode::getChildIndex(KwPlaylistNode* node) const
{
  for (int i = 0; i < m_children.size(); ++i)
  {
    if (m_children[i] == node)
    {
      return i;
    }
  }
  return -1;
}

/// Get the flags for this node.
Qt::ItemFlags KwPlaylistNode::getFlags(Qt::ItemFlags& defaultFlags) const
{
  return defaultFlags;
}

/// Activate the node using a display manager.
void KwPlaylistNode::activate(KwDisplayManager*)
{
}

/// Get a child node by index.
KwPlaylistNode* KwPlaylistNode::_getChild(int index)
{
  Q_UNUSED(index)
  return 0;
}

