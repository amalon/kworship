#ifndef _KwSongdb_h_
#define _KwSongdb_h_

/**
 * @file KwSongdb.h
 * @brief A song database manager class.
 * @author James Hogan <james@albanarts.com>
 */

#include <QHash>
#include <QSqlDatabase>

class KwSongdbSong;
class KwSongdbVersion;

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
     * Accessors
     */

    /// Get a song by id.
    KwSongdbSong* getSongById(int id);

    /** Get a song version by id.
     * This prefetches the song the version is a part of.
     */
    KwSongdbVersion* getSongVersionById(int id);

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
};

#endif // _KwSongdbNode_h_

