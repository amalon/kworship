#ifndef _KwPlaylistSongNode_h_
#define _KwPlaylistSongNode_h_

/**
 * @file KwPlaylistSongNode.h
 * @brief A playlist node for a song.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistNode.h"

class KwPlaylistSong;

/// A playlist node for a song.
class KwPlaylistSongNode : public KwPlaylistNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistSongNode(KwPlaylistNode* parent, KwPlaylistSong* item);

    /// Destructor.
    virtual ~KwPlaylistSongNode();

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
};

#endif // _KwPlaylistSongNode_h_

