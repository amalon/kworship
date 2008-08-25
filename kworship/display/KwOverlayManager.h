#ifndef _KwOverlayManager_h_
#define _KwOverlayManager_h_

/**
 * @file KwOverlayManager.h
 * @brief Overlay manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractDisplayManager.h"

/// Overlay manager.
/**
 * High level interface for controlling overlay notices.
 */
class KwOverlayManager : public KwAbstractDisplayManager
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwOverlayManager();

    /// Destructor.
    virtual ~KwOverlayManager();

};

#endif // _KwOverlayManager_h_

