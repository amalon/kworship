#ifndef _KwAbstractDisplayManager_h_
#define _KwAbstractDisplayManager_h_

/**
 * @file KwAbstractDisplayManager.h
 * @brief Abstract display manager class.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwLocalDisplayController.h"

class KwDisplayMixer;

/// Abstract display manager class.
/**
 * High level interface for controlling a display object.
 */
class KwAbstractDisplayManager
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwAbstractDisplayManager();

    /// Destructor.
    virtual ~KwAbstractDisplayManager();

    /*
     * Main interface
     */

    /// Attach the display to the top of a mixer.
    void attachToMixer(KwDisplayMixer* mixer);

  protected:

    /*
     * Variables
     */

    /// Display object.
    KwLocalDisplayController m_display;
};

#endif // _KwAbstractDisplayManager_h_

