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

#ifndef _KwSongdbSong_h_
#define _KwSongdbSong_h_

/**
 * @file KwSongdbSong.h
 * @brief A song from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include <QString>
#include <QList>

class KwSongdbVersion;

/// A song from the database.
class KwSongdbSong
{
  public:

    /*
     * Types
     */

    /// Version data fields.
    enum Field
    {
      Name = 0x1,
    };
    Q_DECLARE_FLAGS(Fields, Field)

    /*
     * Constructors + destructor
     */

    /** Construct a new song for database insertion.
     * This constructs a blank song which will be inserted into the
     * database when it is saved.
     */
    KwSongdbSong();

    /** Construct from the database.
     * Loads the song information from the database.
     * @param id Database id of song.
     */
    KwSongdbSong(int id);

    /// Destructor.
    virtual ~KwSongdbSong();

    /*
     * Accessors
     */

    /// Get the id.
    int id() const;

    /// Get the name of the song.
    QString name() const;

    /// Get list of song versions.
    QList<KwSongdbVersion*> versions();

    /*
     * Mutators
     */

    /// Set the name.
    void setName(const QString& name);

    /// Save changes to the version data.
    void save();

    /// Register a version object.
    void registerVersion(KwSongdbVersion* version);

  private:

    /*
     * Variables
     */

    /// Song id.
    int m_id;

    /// Which fields have been modified.
    Fields m_modifiedFields;

    /// Name.
    QString m_name;

    /// Whether versions have been loaded.
    bool m_versionsLoaded;

    /// Version ids.
    QList<int> m_versionIds;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(KwSongdbSong::Fields)

#endif // _KwSongdbSong_h_

