#ifndef _KwPlaylistNoteNode_h_
#define _KwPlaylistNoteNode_h_

/**
 * @file KwPlaylistNoteNode.h
 * @brief A playlist node for a note.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistNode.h"

class KwPlaylistNote;

/// A playlist node for a note.
class KwPlaylistNoteNode : public KwPlaylistNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistNoteNode(KwPlaylistNode* parent, KwPlaylistNote* item);

    /// Destructor.
    virtual ~KwPlaylistNoteNode();

    /*
     * Main interface
     */

    virtual QVariant getData(int role, int column);

  private:

    /*
     * Variables
     */

    /// Playlist item.
    KwPlaylistNote* m_item;
};

#endif // _KwPlaylistNoteNode_h_

