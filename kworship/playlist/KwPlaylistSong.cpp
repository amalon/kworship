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
 * @file KwPlaylistSong.cpp
 * @brief A song from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistSong.h"
#include "KwPlaylistSongNode.h"
#include "KwSongdb.h"

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistSong::KwPlaylistSong(KwSongdbVersion* version)
: KwPlaylistItem()
, m_version(version)
{
}

/// Destructor.
KwPlaylistSong::~KwPlaylistSong()
{
}

/*
 * Accessors
 */

/// Get the song version object.
KwSongdbVersion* KwPlaylistSong::getSongVersion()
{
  return m_version;
}

/*
 * Main interface
 */

KwPlaylistNode* KwPlaylistSong::getNode(KwPlaylistNode* parent)
{
  return new KwPlaylistSongNode(parent, this);
}

