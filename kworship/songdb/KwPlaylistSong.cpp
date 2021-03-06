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
 * @file KwPlaylistSong.cpp
 * @brief A song from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistSong.h"
#include "KwPlaylistSongNode.h"
#include "KwSongdbVersion.h"
#include "KwSongdbSong.h"

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistSong::KwPlaylistSong(KwSongdbVersion* version, bool owned)
: KwPlaylistItem()
, m_owned(owned)
, m_version(version)
, m_lyricsLayout(version->lyrics())
{
}

/// Destructor.
KwPlaylistSong::~KwPlaylistSong()
{
  if (m_owned)
  {
    delete m_version->song();
    delete m_version;
  }
}

/*
 * Accessors
 */

/// Get the song version object.
KwSongdbVersion* KwPlaylistSong::getSongVersion() const
{
  return m_version;
}

/// Get the lyrics layout.
KwSongdbLyricsLayout& KwPlaylistSong::getLyricsLayout()
{
  return m_lyricsLayout;
}

/*
 * DOM Translation.
 */

QString KwPlaylistSong::itemType() const
{
  return "song";
}

void KwPlaylistSong::exportDetailsToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const
{
}

/*
 * Main interface
 */

KwPlaylistNode* KwPlaylistSong::getNode(KwPlaylistNode* parent)
{
  return new KwPlaylistSongNode(parent, this);
}

