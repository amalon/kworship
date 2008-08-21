#ifndef _KwPlaylistList_h_
#define _KwPlaylistList_h_

/**
 * @file KwPlaylistList.h
 * @brief A list of playlist items.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistItem.h"

#include <list>

/// A list of playlist items.
/**
 * Inherit from this class for each playlist item type.
 */
class KwPlaylistList : public KwPlaylistItem
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Default constructor.
    KwPlaylistList();

    /// Destructor.
    virtual ~KwPlaylistList();

    /*
     * Child management.
     */

    /// Add a child.
    void addItem(KwPlaylistItem* item);

    /// Get the number of children.
    int getItemCount() const;

    /// Get a specific child.
    KwPlaylistItem* getItem(int index);

    /*
     * Main interface.
     */

    virtual KwPlaylistNode* getNode(KwPlaylistNode* parent);

  private:

    /*
     * Types
     */

    /// List of playlist items.
    typedef std::list<KwPlaylistItem*> Playlist;

    /*
     * Variables
     */

    /// The actual playlist.
    Playlist m_playlist;
    
};

#endif // _KwPlaylistList_h_

