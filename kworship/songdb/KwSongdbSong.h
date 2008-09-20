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

#endif // _KwSongdbNode_h_

