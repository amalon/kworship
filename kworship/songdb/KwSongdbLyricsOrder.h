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

#ifndef _KwSongdbLyricsOrder_h_
#define _KwSongdbLyricsOrder_h_

/**
 * @file KwSongdbLyricsOrder.h
 * @brief An order item for a song from the database.
 * @author James Hogan <james@albanarts.com>
 */

class KwSongdbLyrics;

/// An order item for a song from the database.
class KwSongdbLyricsOrder
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwSongdbLyricsOrder(int order, KwSongdbLyrics* lyrics);

    /// Destructor.
    virtual ~KwSongdbLyricsOrder();

    /*
     * Accessors
     */

    /// Get the order.
    int getOrder() const;

    /// Get the lyrics object.
    KwSongdbLyrics* getLyrics() const;

  private:

    /*
     * Variables
     */

    /// Lyrics order.
    int m_order;

    /// Lyrics object.
    KwSongdbLyrics* m_lyrics;
};

#endif // _KwSongdbLyricsOrder_h_

