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
 * @file KwPlaylistFileNode.cpp
 * @brief A playlist node for a file.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistFileNode.h"
#include "KwPlaylistFile.h"

#include <KMimeType>
#include <KIcon>

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistFileNode::KwPlaylistFileNode(KwPlaylistNode* parent, KwPlaylistFile* item)
: KwPlaylistNode(parent)
, m_item(item)
{
}

/// Destructor.
KwPlaylistFileNode::~KwPlaylistFileNode()
{
}

/*
 * Main interface
 */

QVariant KwPlaylistFileNode::getData(int role, int column)
{
  if (role == Qt::DisplayRole)
  {
    if (column == 0)
    {
      return m_item->getUrl().toString();
    }
  }
  else if (role == Qt::DecorationRole)
  {
    if (column == 0)
    {
      KMimeType::Ptr mimeType = KMimeType::findByUrl(m_item->getUrl());
      return KIcon(mimeType->iconName());
    }
  }
  return QVariant();
}

void KwPlaylistFileNode::activate(KwDisplayManager* manager)
{
  m_item->activate(manager);
}

