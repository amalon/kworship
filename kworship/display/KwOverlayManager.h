#ifndef _KwOverlayManager_h_
#define _KwOverlayManager_h_

/**
 * @file KwOverlayManager.h
 * @brief Overlay manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractDisplayManager.h"

class KwCssScope;

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

    /*
     * Main interface
     */

    /// Apply the styles in a scope.
    void applyStyles(KwCssScope* scope);
};

#endif // _KwOverlayManager_h_

