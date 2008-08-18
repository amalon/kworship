#ifndef _KwPlaylistListNode_h_
#define _KwPlaylistListNode_h_

/**
 * @file KwPlaylistListNode.h
 * @brief A playlist node for a list.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistNode.h"

class KwPlaylistList;

/// A playlist node for a list.
class KwPlaylistListNode : public KwPlaylistNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistListNode(KwPlaylistList* item);

    /// Destructor.
    virtual ~KwPlaylistListNode();

    /*
     * Main interface
     */

    virtual QVariant getData(int role, int column);

    virtual int getChildCount() const;

    virtual KwPlaylistNode* getChild(int index);
  private:

    /*
     * Variables
     */

    /// Playlist item.
    KwPlaylistList* m_item;
};

#endif // _KwPlaylistListNode_h_

