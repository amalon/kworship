#ifndef _KwSongdbSong_h_
#define _KwSongdbSong_h_

/**
 * @file KwSongdbSong.h
 * @brief A song from the database.
 * @author James Hogan <james@albanarts.com>
 */

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

  private:

    /*
     * Variables
     */

    /// Song id.
    int m_id;
};

#endif // _KwSongdbNode_h_

