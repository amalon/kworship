#ifndef _KwSongdbVersion_h_
#define _KwSongdbVersion_h_

/**
 * @file KwSongdbVersion.h
 * @brief A song version from the database.
 * @author James Hogan <james@albanarts.com>
 */

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

  private:

    /*
     * Variables
     */

    /// Version id.
    int m_id;
};

#endif // _KwSongdbNode_h_

