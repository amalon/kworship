#ifndef _KwAbstractLayer_h_
#define _KwAbstractLayer_h_

/**
 * @file KwAbstractLayer.h
 * @brief Layer interface class.
 * @author James Hogan <james@albanarts.com>
 */

#include <QSize>

class QWidget;

/// Abstract layer as part of display.
class KwAbstractLayer
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwAbstractLayer();

    /// Destructor.
    virtual ~KwAbstractLayer();

    /*
     * Methods
     */

    /// Add widgets for this layer.
    virtual void* addWidgets(QWidget* master) const = 0;

    /// Remove the widgets generated by addWidgets.
    virtual void removeWidgets(QWidget* master, void* data) const = 0;
};

#endif // _KwAbstractLayer_h_

