#ifndef _KwBackgroundManager_h_
#define _KwBackgroundManager_h_

/**
 * @file KwBackgroundManager.h
 * @brief Background manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractDisplayManager.h"

#include <QPixmap>

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
    KwBackgroundManager();

    /// Destructor.
    virtual ~KwBackgroundManager();

    /*
     * Main interface
     */

    /// Set the background to an image.
    void setImage(const QPixmap& pixmap);

    /// Set the background to a video.
    void setVideo(QString path);
};

#endif // _KwBackgroundManager_h_

