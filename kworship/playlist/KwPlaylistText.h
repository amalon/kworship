#ifndef _KwPlaylistText_h_
#define _KwPlaylistText_h_

/**
 * @file KwPlaylistText.h
 * @brief A plain text playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistItem.h"

/// A plain text playlist item.
class KwPlaylistText : public KwPlaylistItem
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Default constructor.
    KwPlaylistText();

    /// Destructor.
    virtual ~KwPlaylistText();
};

#endif // _KwPlaylistText_h_

