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

#ifndef _KwSongdbSong_h_
#define _KwSongdbSong_h_

/**
 * @file KwSongdbSong.h
 * @brief A song from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include <QString>

/// A song from the database.
class KwSongdbSong
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwSongdbSong(int id);

    /// Destructor.
    virtual ~KwSongdbSong();

    /*
     * Accessors
     */

    /// Get the id.
    int getId() const;

    /// Get the name of the song.
    QString getName() const;

  private:

    /*
     * Variables
     */

    /// Song id.
    int m_id;

    /// Name.
    QString m_name;
};

#endif // _KwSongdbSong_h_

