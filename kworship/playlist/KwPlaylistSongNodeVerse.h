#ifndef _KwPlaylistSongNodeVerse_h_
#define _KwPlaylistSongNodeVerse_h_

/**
 * @file KwPlaylistSongNodeVerse.h
 * @brief A playlist node for a song verse.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistNode.h"

class KwPlaylistSong;

/// A playlist node for a song verse.
class KwPlaylistSongNodeVerse : public KwPlaylistNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistSongNodeVerse(KwPlaylistNode* parent, KwPlaylistSong* item, int verse);

    /// Destructor.
    virtual ~KwPlaylistSongNodeVerse();

    /*
     * Main interface
     */

    virtual QVariant getData(int role, int column);

  private:

    /*
     * Variables
     */

    /// Playlist item.
    KwPlaylistSong* m_item;

    /// Verse number.
    int m_verse;
};

#endif // _KwPlaylistSongNodeVerse_h_

