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
 * @file KwSongdbVersionNode.cpp
 * @brief A node for a song version.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbVersionNode.h"

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwSongdbVersionNode::KwSongdbVersionNode(KwSongdbNode* parent, QString label, int id)
: KwSongdbNode(parent)
, m_label(label)
, m_id(id)
{
  if (m_label == "")
  {
    m_label = "Default version";
  }
}

/// Destructor.
KwSongdbVersionNode::~KwSongdbVersionNode()
{
}

/*
 * Main interface
 */

/// Get data associated with the node.
QVariant KwSongdbVersionNode::getData(int role, int column)
{
  if (role == Qt::DisplayRole)
  {
    if (column == 0)
    {
      return m_label;
    }
  }
  return QVariant();
}

/// Get flags for this item.
Qt::ItemFlags KwSongdbVersionNode::getFlags(Qt::ItemFlags defaultFlags) const
{
  return Qt::ItemIsDragEnabled | defaultFlags;
}

/// Get mime data string for this set of songs.
QString KwSongdbVersionNode::mimeData()
{
  return QString("songdb %1").arg(m_id);
}

