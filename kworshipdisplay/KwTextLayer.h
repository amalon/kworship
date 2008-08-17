#ifndef _KwTextLayer_h_
#define _KwTextLayer_h_

/**
 * @file KwTextLayer.h
 * @brief Layer of pretty text.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractLayer.h"
#include "KwTextStyle.h"

#include <QSize>
#include <QPixmap>

/// Layer of pretty text.
class KwTextLayer : public KwAbstractLayer
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwTextLayer();

    /// Primaryt constructor.
    KwTextLayer(QString text);

    /// Destructor.
    virtual ~KwTextLayer();

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

    /// Text style.
    KwTextStyle m_style;

    /// The actual text.
    QString m_text;
};

#endif // _KwTextLayer_h_

