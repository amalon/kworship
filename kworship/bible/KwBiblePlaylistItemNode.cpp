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
 * @file KwBiblePlaylistItemNode.cpp
 * @brief A playlist node for a bible passage item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBiblePlaylistItemNode.h"
#include "KwBiblePlaylistItem.h"
#include "KwBiblePassage.h"
#include <KwDisplayManager.h>

#include <KIcon>

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwBiblePlaylistItemNode::KwBiblePlaylistItemNode(KwPlaylistNode* parent, KwBiblePlaylistItem* item)
: KwPlaylistNode(parent)
, m_item(item)
{
}

/// Destructor.
KwBiblePlaylistItemNode::~KwBiblePlaylistItemNode()
{
}

/*
 * Main interface
 */

QVariant KwBiblePlaylistItemNode::getData(int role, int column)
{
  if (role == Qt::DisplayRole)
  {
    if (column == 0)
    {
      return m_item->passage().textualKey();
    }
  }
  else if (role == Qt::DecorationRole)
  {
    if (column == 0)
    {
      return KIcon("bible");
    }
  }
  return QVariant();
}

void KwBiblePlaylistItemNode::activate(KwDisplayManager* manager)
{
  manager->applyStyles(m_item);
  // Set html
  manager->text.setHtml(m_item->passage().renderedText());
}

