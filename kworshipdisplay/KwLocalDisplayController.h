#ifndef _KwLocalDisplayController_h_
#define _KwLocalDisplayController_h_

/**
 * @file KwLocalDisplayController.h
 * @brief Concretisation of KwAbstractDisplay.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractDisplay.h"

/// Concretisation of KwAbstractDisplay.
class KwLocalDisplayController : public KwAbstractDisplay
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwLocalDisplayController();

    /// Destructor.
    virtual ~KwLocalDisplayController();
};

#endif // _KwLocalDisplayController_h_

