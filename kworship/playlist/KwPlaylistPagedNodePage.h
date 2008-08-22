#ifndef _KwPlaylistPagedNodePage_h_
#define _KwPlaylistPagedNodePage_h_

/**
 * @file KwPlaylistPagedNodePage.h
 * @brief A playlist node for a page of a paged text item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistNode.h"

class KwPlaylistPaged;

/// A playlist node for a page of a paged text item.
class KwPlaylistPagedNodePage : public KwPlaylistNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistPagedNodePage(KwPlaylistNode* parent, KwPlaylistPaged* item, unsigned int page);

    /// Destructor.
    virtual ~KwPlaylistPagedNodePage();

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
    KwPlaylistPaged* m_item;

    /// Page number.
    unsigned int m_page;
};

#endif // _KwPlaylistPagedNodePage_h_

