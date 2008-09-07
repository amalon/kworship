#ifndef _KwLoggingDisplay_h_
#define _KwLoggingDisplay_h_

/**
 * @file KwLoggingDisplay.h
 * @brief Logging controller of displays.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractDisplay.h"
#include "KwLayerData.h"

/// Logging controller of displays.
class KwLoggingDisplay : public KwAbstractDisplay
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwLoggingDisplay();

    /// Destructor.
    virtual ~KwLoggingDisplay();

  protected:

    /*
     * Main interface events for extension
     */

    /// @copydoc KwAbstractDisplay::setDisplayResolutionEvent(QSize)
    virtual void setDisplayResolutionEvent(QSize size);

    /// @copydoc KwAbstractDisplay::clearLayersEvent()
    virtual void clearLayersEvent();

    /// @copydoc KwAbstractDisplay::setLayerEvent(unsigned int, const KwAbstractLayer*, bool)
    virtual void setLayerEvent(unsigned int index, const KwAbstractLayer* layer, bool insert);

    /// @copydoc KwAbstractDisplay::removeLayerEvent(unsigned int)
    virtual void removeLayerEvent(unsigned int index);

  private:

    /*
     * Types
     */

    /// Data per layer.
    typedef KwLayerData<int> LayerData;

    /*
     * Variables
     */

    /// To store some random data.
    LayerData m_layerWidgetData;
};

#endif // _KwLoggingDisplay_h_

