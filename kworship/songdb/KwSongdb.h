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

#ifndef _KwSongdb_h_
#define _KwSongdb_h_

/**
 * @file KwSongdb.h
 * @brief A song database manager class.
 * @author James Hogan <james@albanarts.com>
 */

#include <QHash>
#include <QList>
#include <QSqlDatabase>

class KwSongdbSong;
class KwSongdbVersion;
class KwSongdbSongBook;

#define KW_SONGDB_QUERY(query) KwSongdb::self()->handleQuery(query,__FILE__,__LINE__)

/// A song database manager class.
class KwSongdb
{
  public:

    /*
     * Singletonhood
     */

    /// Get the one instance of this class.
    static KwSongdb* self();

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwSongdb(QSqlDatabase& db);

    /// Destructor.
    virtual ~KwSongdb();

    /*
     * Functionality.
     */

    /** Detect errors and handle nicely.
     * @param query SQL query to check the result of.
     * @return Whether the query was successful.
     */
    bool handleQuery(QSqlQuery &query, const char *src = 0, int line = 0);

    /*
     * Accessors
     */

    /// Get the database.
    QSqlDatabase database();

    /// Get a song by id.
    KwSongdbSong* songById(int id);

    /** Get a song version by id.
     * This prefetches the song the version is a part of.
     */
    KwSongdbVersion* songVersionById(int id);

    /// Get song versions by ids.
    QList<KwSongdbVersion*> songVersionsByIds(const QList<int>& ids);

    /// Get song book by id.
    KwSongdbSongBook* songBookById(int id);

    /// Get all song books.
    QList<KwSongdbSongBook*> songBooks();

    /*
     * Mutators
     */

    /// Register a song object.
    void registerSong(KwSongdbSong* song);

    /// Register a version object.
    void registerVersion(KwSongdbVersion* version);

    /// Register a song book.
    void registerSongBook(KwSongdbSongBook* songBook);

  private:
    
    /*
     * Singletonhood
     */

    /// The one instance of this class.
    static KwSongdb* s_singleton;

    /*
     * Variables
     */

    /// Qt database object.
    QSqlDatabase m_database;

    /*
     * Cache of database objects
     */

    /// Song.
    typedef QHash<int, KwSongdbSong*> SongHash;
    SongHash m_songsById;

    /// Song versions.
    typedef QHash<int, KwSongdbVersion*> VersionHash;
    VersionHash m_versionsById;

    /// Song books.
    typedef QHash<int, KwSongdbSongBook*> SongBookHash;
    SongBookHash m_songBooksById;
};

#endif // _KwSongdb_h_

