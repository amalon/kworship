#ifndef _KwPlaylistItem_h_
#define _KwPlaylistItem_h_

/**
 * @file KwPlaylistItem.h
 * @brief An item that can be added to a playlist.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssScope.h"

class KwPlaylistNode;

/// An item that can be added to a playlist.
/**
 * Inherit from this class for each playlist item type.
 */
class KwPlaylistItem : public KwCssScope
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Default constructor.
    KwPlaylistItem();

    /// Destructor.
    virtual ~KwPlaylistItem();

    /*
     * Main interface.
     */

    /// Get a tree node for this item.
    virtual KwPlaylistNode* getNode(KwPlaylistNode* parent) = 0;
};

#endif // _KwPlaylistItem_h_

