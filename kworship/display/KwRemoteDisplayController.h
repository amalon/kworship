#ifndef _KwRemoteDisplayController_h_
#define _KwRemoteDisplayController_h_

/**
 * @file KwRemoteDisplayController.h
 * @brief Display server class that passes control from the remote controller.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractDisplay.h"

/// Display server class that passes control from the remote controller.
class KwRemoteDisplayController : public KwAbstractDisplay
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwRemoteDisplayController();

    /// Destructor.
    virtual ~KwRemoteDisplayController();
};

#endif // _KwRemoteDisplayController_h_

