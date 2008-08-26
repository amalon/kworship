#ifndef _KwPlaylistVideo_h_
#define _KwPlaylistVideo_h_

/**
 * @file KwPlaylistVideo.h
 * @brief A media playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistFile.h"

#include "KwMediaItem.h"

/// A media playlist item.
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

  private:

    /*
     * Variables
     */

    /// Video item
    KwMediaItem m_mediaItem;
};

#endif // _KwPlaylistVideo_h_

