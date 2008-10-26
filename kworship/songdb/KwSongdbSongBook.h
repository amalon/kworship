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

#ifndef _KwSongdbSongBook_h_
#define _KwSongdbSongBook_h_

/**
 * @file KwSongdbSongBook.h
 * @brief A song book of songs from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include <QString>
#include <QFlags>

/// A song book of songs from the database.
class KwSongdbSongBook
{
  public:

    /*
     * Types
     */

    /// Version data fields.
    enum Field
    {
      Abreviation = 0x1,
      Name = 0x2,
      Description = 0x4
    };
    Q_DECLARE_FLAGS(Fields, Field)

    /*
     * Constructors + destructor
     */

    /** Construct a new song book for database insertion.
     * This constructs a blank song book which will be inserted into the
     * database when it is saved.
     */
    KwSongdbSongBook();

    /** Construct from the database.
     * Loads the song book information from the database.
     * @param id Database id of song book.
     */
    KwSongdbSongBook(int id);

    /// Destructor.
    virtual ~KwSongdbSongBook();

    /*
     * Accessors
     */

    /// Get the id.
    int id() const;

    /// Get the abreviation of the song book.
    QString abreviation() const;

    /// Get the name of the song book.
    QString name() const;

    /// Get the description of the song book.
    QString description() const;

    /*
     * Mutators
     */

    /// Set the abreviation.
    void setAbreviation(const QString& abreviation);

    /// Set the name.
    void setName(const QString& name);

    /// Set the description.
    void setDescription(const QString& description);

    /// Save changes to the song book data.
    void save();

  private:

    /*
     * Variables
     */

    /// Song book id.
    int m_id;

    /// Which fields have been modified.
    Fields m_modifiedFields;

    /// Short abreviation text.
    QString m_abreviation;

    /// Name.
    QString m_name;

    /// Description.
    QString m_description;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(KwSongdbSongBook::Fields)

#endif // _KwSongdbSongBook_h_

