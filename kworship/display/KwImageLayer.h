#ifndef _KwImageLayer_h_
#define _KwImageLayer_h_

/**
 * @file KwImageLayer.h
 * @brief Background image layer.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractLayer.h"

#include <QSize>
#include <QPixmap>

/// Background image layer.
class KwImageLayer : public KwAbstractLayer
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwImageLayer();

    /// Primary constructor.
    KwImageLayer(const QPixmap& pixmap);

    /// Destructor.
    virtual ~KwImageLayer();

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

    /// Pixmap image.
    QPixmap m_pixmap;

    /// Whether to stretch the image to fit the screen.
    bool m_stretch;

    /// Whether to keep the aspect ratio of the image.
    bool m_keepAspect;
};

#endif // _KwImageLayer_h_

