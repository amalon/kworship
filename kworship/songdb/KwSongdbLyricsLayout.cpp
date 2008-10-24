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
 * @file KwSongdbLyricsLayout.cpp
 * @brief Manipulates a layout of lyrics.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbLyricsLayout.h"

#include "compiler.h"

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwSongdbLyricsLayout::KwSongdbLyricsLayout(const KwSongdbLyrics& lyrics)
: m_lyrics(lyrics)
, m_pageCache(lyrics.plainVerses())
{
}

/// Destructor.
KwSongdbLyricsLayout::~KwSongdbLyricsLayout()
{
}

/*
 * Pagination
 */

/// Get the number of pages.
int KwSongdbLyricsLayout::numPages() const
{
  return m_pageCache.size();
}

/// Get the plain text content of a page.
QString KwSongdbLyricsLayout::pageContent(int page) const
{
  if (likely(page > 0 && page < m_pageCache.size()))
  {
    return m_pageCache[page];
  }
  else
  {
    return QString();
  }
}

