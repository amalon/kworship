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

#ifndef _KwSongdbLyricsLayout_h_
#define _KwSongdbLyricsLayout_h_

/**
 * @file KwSongdbLyricsLayout.h
 * @brief Manipulates a layout of lyrics.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbLyrics.h"

/// Manipulates a layout of lyrics.
class KwSongdbLyricsLayout
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    explicit KwSongdbLyricsLayout(const KwSongdbLyrics& lyrics);

    /// Destructor.
    virtual ~KwSongdbLyricsLayout();

    /*
     * Pagination
     */

    /// Get the number of pages.
    int numPages() const;

    /// Get the plain text content of a page.
    QString pageContent(int page) const;

  private:

    /*
     * Variables
     */

    /// Lyrics.
    const KwSongdbLyrics& m_lyrics;

    /// Pages cache.
    QStringList m_pageCache;
};

#endif // _KwSongdbLyricsLayout_h_

