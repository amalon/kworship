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

#ifndef _KwSongdbSongBookSong_h_
#define _KwSongdbSongBookSong_h_

/**
 * @file KwSongdbSongBookSong.h
 * @brief A song book song from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include <QString>
#include <QFlags>

class KwSongdbSongBook;
class KwSongdbVersion;

/// A song book song from the database.
class KwSongdbSongBookSong
{
  public:

    /*
     * Types
     */

    /// Version data fields.
    enum Field
    {
      SongBook = 0x1,
      SongNumber = 0x2,
      Version = 0x4
    };
    Q_DECLARE_FLAGS(Fields, Field)

    /*
     * Constructors + destructor
     */

    /** Construct a new song book song for database insertion.
     * This constructs a blank song book song which will be inserted into the
     * database when it is saved.
     */
    KwSongdbSongBookSong();

    /** Construct from the database from data.
     * @param songBook Song book object.
     * @param songNumber Number in the song book that the song is.
     * @param version Version at the song position.
     */
    KwSongdbSongBookSong(KwSongdbSongBook* songBook, int songNumber, KwSongdbVersion* version);

    /// Destructor.
    virtual ~KwSongdbSongBookSong();

    /*
     * Accessors
     */

    /// Get the song book.
    KwSongdbSongBook* songBook();

    /// Get the song number in the song book.
    int songNumber() const;

    /// Get the song version.
    KwSongdbVersion* version();

    /*
     * Mutators
     */

    /// Set the song book.
    void setSongBook(KwSongdbSongBook* songBook);

    /// Set the song number in the song book.
    void setSongNumber(int songNumber);

    /// Set the song version.
    void setVersion(KwSongdbVersion* version);

    /// Save changes to the song book data.
    void save();

  private:

    /*
     * Variables
     */

    /// Original song book id.
    int m_originalSongBookId;

    /// Original song book number.
    int m_originalSongNumber;

    /// Which fields have been modified.
    Fields m_modifiedFields;

    /// Song book.
    KwSongdbSongBook* m_songBook;

    /// Song book number.
    int m_songNumber;

    /// Version.
    KwSongdbVersion* m_version;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(KwSongdbSongBookSong::Fields)

#endif // _KwSongdbSongBookSong_h_

