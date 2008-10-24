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
 * @file KwPlaylistSongNodeVerse.cpp
 * @brief A playlist node for a song verse.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistSongNodeVerse.h"
#include "KwPlaylistSong.h"
#include "KwSongdbVersion.h"
#include "KwSongdbLyrics.h"
#include "KwDisplayManager.h"

#include <KIcon>

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistSongNodeVerse::KwPlaylistSongNodeVerse(KwPlaylistNode* parent, KwPlaylistSong* item, int verse)
: KwPlaylistNode(parent)
, m_item(item)
, m_verse(verse)
{
}

/// Destructor.
KwPlaylistSongNodeVerse::~KwPlaylistSongNodeVerse()
{
}

/*
 * Main interface
 */

QVariant KwPlaylistSongNodeVerse::getData(int role, int column)
{
  if (role == Qt::DisplayRole)
  {
    if (column == 0)
    {
      return m_item->getSongVersion()->lyricsByOrder(m_verse)->lyrics();
    }
  }
  else if (role == Qt::DecorationRole)
  {
    if (column == 0)
    {
      return KIcon("song");
    }
  }
  return QVariant();
}

void KwPlaylistSongNodeVerse::activate(KwDisplayManager* manager)
{
  manager->applyStyles(m_item);
  // Set text
  manager->text.setText(m_item->getSongVersion()->lyricsByOrder(m_verse)->lyrics());
}

