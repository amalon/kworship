#ifndef _KwPlaylistVideo_h_
#define _KwPlaylistVideo_h_

/**
 * @file KwPlaylistVideo.h
 * @brief An video playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistFile.h"

/// An video playlist item.
class KwPlaylistVideo : public KwPlaylistFile
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistVideo(QString url);

    /// Destructor.
    virtual ~KwPlaylistVideo();

    /*
     * Main interface.
     */

    virtual void activate(KwDisplayManager* manager);
};

#endif // _KwPlaylistVideo_h_

