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

#ifndef _KwSongdbLyrics_h_
#define _KwSongdbLyrics_h_

/**
 * @file KwSongdbLyrics.h
 * @brief Contains and manupulates a set of song lyrics.
 * @author James Hogan <james@albanarts.com>
 */

#include <QString>
#include <QStringList>

/// Contains and manupulates a set of song lyrics.
class KwSongdbLyrics
{
  public:

    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwSongdbLyrics();

    /// Primary constructor.
    KwSongdbLyrics(const QString& markup);

    /// Destructor.
    virtual ~KwSongdbLyrics();

    /*
     * Accessors
     */

    /// Get the markup for these lyrics.
    QString markup() const;

    /// Get verses of lyrics in plain text.
    QStringList plainVerses() const;

    /*
     * Mutators
     */

    /// Set the lyrics from markup.
    void setMarkup(const QString& markup);

  private:

    /*
     * Variables
     */

    /// Source lyric markup.
    QString m_markup;
};

#endif // _KwSongdbLyrics_h_

