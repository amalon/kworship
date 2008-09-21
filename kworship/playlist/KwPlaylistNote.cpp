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
 * @file KwPlaylistNote.cpp
 * @brief A plain text playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistNote.h"
#include "KwPlaylistNoteNode.h"

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistNote::KwPlaylistNote(QString content)
: KwPlaylistItem()
, m_content(content)
{
}

/// Destructor.
KwPlaylistNote::~KwPlaylistNote()
{
}

/*
 * Main interface.
 */

/// Get the text.
QString KwPlaylistNote::getContent() const
{
  return m_content;
}

KwPlaylistNode* KwPlaylistNote::getNode(KwPlaylistNode* parent)
{
  return new KwPlaylistNoteNode(parent, this);
}

