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
 * @file KwPlaylistUnknownNode.cpp
 * @brief A playlist node for an unknown item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistUnknownNode.h"
#include "KwPlaylistUnknown.h"

#include <KIcon>
#include <KLocale>

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistUnknownNode::KwPlaylistUnknownNode(KwPlaylistNode* parent, KwPlaylistUnknown* item)
: KwPlaylistNode(parent)
, m_item(item)
{
}

/// Destructor.
KwPlaylistUnknownNode::~KwPlaylistUnknownNode()
{
}

/*
 * Main interface
 */

QVariant KwPlaylistUnknownNode::getData(int role, int column)
{
  if (role == Qt::DisplayRole)
  {
    if (column == 0)
    {
      return i18n("Unrecognised playlist item of type '%1'").arg(m_item->itemType());
    }
  }
  else if (role == Qt::DecorationRole)
  {
    if (column == 0)
    {
      return KIcon("unknown");
    }
  }
  return QVariant();
}

KwPlaylistItem *KwPlaylistUnknownNode::playlistItem() const
{
  return m_item;
}
