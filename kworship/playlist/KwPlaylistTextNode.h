#ifndef _KwPlaylistTextNode_h_
#define _KwPlaylistTextNode_h_

/**
 * @file KwPlaylistTextNode.h
 * @brief A playlist node for a text.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistPagedNode.h"

class KwPlaylistText;

/// A playlist node for a text.
class KwPlaylistTextNode : public KwPlaylistPagedNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistTextNode(KwPlaylistNode* parent, KwPlaylistText* item);

    /// Destructor.
    virtual ~KwPlaylistTextNode();

    /*
     * Main interface
     */

    virtual QVariant getData(int role, int column);

  private:

    /*
     * Variables
     */

    /// Playlist item.
    KwPlaylistText* m_item;
};

#endif // _KwPlaylistTextNode_h_

