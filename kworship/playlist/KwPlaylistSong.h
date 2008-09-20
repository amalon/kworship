#ifndef _KwPlaylistSong_h_
#define _KwPlaylistSong_h_

/**
 * @file KwPlaylistSong.h
 * @brief A song playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistItem.h"

class KwSongdbVersion;

/// A song playlist item.
class KwPlaylistSong : public KwPlaylistItem
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistSong(KwSongdbVersion* version);

    /// Destructor.
    virtual ~KwPlaylistSong();

    /*
     * Accessors
     */

    /// Get the song version object.
    KwSongdbVersion* getSongVersion();

    /*
     * Main interface
     */

    virtual KwPlaylistNode* getNode(KwPlaylistNode* parent);

  private:
    
    /*
     * Variables
     */

    /// Song version.
    KwSongdbVersion* m_version;
};

#endif // _KwPlaylistSong_h_

