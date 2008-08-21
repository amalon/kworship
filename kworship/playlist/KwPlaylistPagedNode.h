#ifndef _KwPlaylistPagedNode_h_
#define _KwPlaylistPagedNode_h_

/**
 * @file KwPlaylistPagedNode.h
 * @brief A playlist node for a paged text item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistNode.h"

class KwPlaylistPaged;

/// A playlist node for a text.
class KwPlaylistPagedNode : public KwPlaylistNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistPagedNode(KwPlaylistNode* parent, KwPlaylistPaged* item);

    /// Destructor.
    virtual ~KwPlaylistPagedNode();

    /*
     * Main interface
     */

    virtual int getChildCount() const;

  protected:
    virtual KwPlaylistNode* _getChild(int index);

  private:

    /*
     * Variables
     */

    /// Playlist item.
    KwPlaylistPaged* m_item;
};

#endif // _KwPlaylistPagedNode_h_

