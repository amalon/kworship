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
 * @file KwSongdbLyricsOrder.cpp
 * @brief An order item for a song from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbLyricsOrder.h"

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwSongdbLyricsOrder::KwSongdbLyricsOrder(int order, KwSongdbLyrics* lyrics)
: m_order(order)
, m_lyrics(lyrics)
{
}

/// Destructor.
KwSongdbLyricsOrder::~KwSongdbLyricsOrder()
{
}

/*
 * Accessors
 */

/// Get the order.
int KwSongdbLyricsOrder::getOrder() const
{
  return m_order;
}

/// Get the lyrics object.
KwSongdbLyrics* KwSongdbLyricsOrder::getLyrics() const
{
  return m_lyrics;
}

