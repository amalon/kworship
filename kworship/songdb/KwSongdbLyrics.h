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

#ifndef _KwSongdbLyrics_h_
#define _KwSongdbLyrics_h_

/**
 * @file KwSongdbLyrics.h
 * @brief A verse of lyrics from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include <QString>

/// A verse of lyrics from the database.
class KwSongdbLyrics
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwSongdbLyrics(int id, const QString& lyrics);

    /// Destructor.
    virtual ~KwSongdbLyrics();

    /*
     * Accessors
     */

    /// Get lyrics id.
    int getId() const;

    /// Get the lyrics.
    QString getLyrics() const;

  private:

    /*
     * Variables
     */

    /// Lyrics id.
    int m_id;

    /// Actual lyrics.
    QString m_lyrics;
};

#endif // _KwSongdbLyrics_h_

