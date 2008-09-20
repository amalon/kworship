#ifndef _KwPlaylistImage_h_
#define _KwPlaylistImage_h_

/**
 * @file KwPlaylistImage.h
 * @brief An image playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistFile.h"

/// An image playlist item.
class KwPlaylistImage : public KwPlaylistFile
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistImage(const QUrl& url);

    /// Destructor.
    virtual ~KwPlaylistImage();

    /*
     * Main interface.
     */

    virtual void activate(KwDisplayManager* manager);
};

#endif // _KwPlaylistImage_h_

