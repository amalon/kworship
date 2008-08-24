#ifndef _KwPlaylistFileNode_h_
#define _KwPlaylistFileNode_h_

/**
 * @file KwPlaylistFileNode.h
 * @brief A playlist node for a file.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistNode.h"

class KwPlaylistFile;

/// A playlist node for a file.
class KwPlaylistFileNode : public KwPlaylistNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistFileNode(KwPlaylistNode* parent, KwPlaylistFile* item);

    /// Destructor.
    virtual ~KwPlaylistFileNode();

    /*
     * Main interface
     */

    virtual QVariant getData(int role, int column);

    virtual void activate(KwDisplayManager* manager);

  private:

    /*
     * Variables
     */

    /// Playlist item.
    KwPlaylistFile* m_item;
};

#endif // _KwPlaylistFileNode_h_

