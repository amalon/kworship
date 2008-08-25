#ifndef _KwVideoLayer_h_
#define _KwVideoLayer_h_

/**
 * @file KwVideoLayer.h
 * @brief Background video layer.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractLayer.h"

#include <QSize>
#include <QPixmap>

namespace Phonon
{
  class MediaObject;
}

/// Background video layer.
class KwVideoLayer : public KwAbstractLayer
{
  public:

    /*
     * Constructors + destructors
     */

    /// Primary constructor.
    KwVideoLayer(Phonon::MediaObject* media);

    /// Destructor.
    virtual ~KwVideoLayer();

    /*
     * Methods
     */

    /// @copydoc KwAbstractLayer::addWidgets(QWidget*) const
    virtual void* addWidgets(QWidget* master) const;

    /// @copydoc KwAbstractLayer::removeWidgets(QWidget*,void*) const
    virtual void removeWidgets(QWidget* master, void* data) const;

  private:

    /*
     * Variables
     */

    /// Media object.
    Phonon::MediaObject* m_media;

    /// Whether to stretch the video to fit the screen.
    bool m_stretch;

    /// Whether to keep the aspect ratio of the video.
    bool m_keepAspect;
};

#endif // _KwVideoLayer_h_
