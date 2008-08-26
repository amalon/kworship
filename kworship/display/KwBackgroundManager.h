#ifndef _KwBackgroundManager_h_
#define _KwBackgroundManager_h_

/**
 * @file KwBackgroundManager.h
 * @brief Background manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractDisplayManager.h"

#include <QPixmap>

class KwMediaManager;
class KwMediaItemVideo;

class KwImageLayer;
class KwVideoLayer;

/// Background manager.
/**
 * High level interface for controlling backgrounds.
 */
class KwBackgroundManager : public KwAbstractDisplayManager
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwBackgroundManager(KwMediaManager* mediaManager);

    /// Destructor.
    virtual ~KwBackgroundManager();

    /*
     * Main interface
     */

    /// Clear the background.
    void clear();

    /// Set the background to an image.
    void setImage(const QPixmap& pixmap);

    /// Set the background up forvideo.
    void setVideo();

  private:

    /*
     * Variables
     */

    /// Media manager.
    KwMediaManager* m_mediaManager;

    /// Image layer.
    KwImageLayer* m_imageLayer;

    /// Video layer.
    KwVideoLayer* m_videoLayer;
};

#endif // _KwBackgroundManager_h_

