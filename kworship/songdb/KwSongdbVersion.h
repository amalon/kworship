#ifndef _KwSongdbVersion_h_
#define _KwSongdbVersion_h_

/**
 * @file KwSongdbVersion.h
 * @brief A song version from the database.
 * @author James Hogan <james@albanarts.com>
 */

class KwSongdbSong;

/// A song version from the database.
class KwSongdbVersion
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwSongdbVersion(int id);

    /// Destructor.
    virtual ~KwSongdbVersion();

    /*
     * Accessors
     */

    /// Get the song this is a version of.
    KwSongdbSong* getSong();

  private:

    /*
     * Variables
     */

    /// Version id.
    int m_id;

    /// Song object.
    KwSongdbSong* m_song;
};

#endif // _KwSongdbNode_h_

