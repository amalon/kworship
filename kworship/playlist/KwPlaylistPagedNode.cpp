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
 * @file KwPlaylistPagedNode.cpp
 * @brief A playlist node for a text.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistPaged.h"
#include "KwPlaylistPagedNode.h"
#include "KwPlaylistPagedNodePage.h"

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistPagedNode::KwPlaylistPagedNode(KwPlaylistNode* parent, KwPlaylistPaged* item)
: KwPlaylistNode(parent)
, m_item(item)
{
}

/// Destructor.
KwPlaylistPagedNode::~KwPlaylistPagedNode()
{
}

/*
 * Main interface
 */

int KwPlaylistPagedNode::getChildCount() const
{
  return m_item->getPageCount();
}

KwPlaylistNode* KwPlaylistPagedNode::_getChild(int index)
{
  return new KwPlaylistPagedNodePage(this, m_item, index);
}

