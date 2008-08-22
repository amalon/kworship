#ifndef _KwDisplayManager_h_
#define _KwDisplayManager_h_

/**
 * @file KwDisplayManager.h
 * @brief Display manager class.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwDisplayMixer.h"
#include "KwBackgroundManager.h"
#include "KwTextManager.h"
#include "KwOverlayManager.h"

/// Abstract display management.
/**
 * High level interface for controlling a display object.
 */
class KwDisplayManager
{
  public:

    /*
     * Manager variables
     */

    /// Background manager.
    KwBackgroundManager background;

    /// Text manager.
    KwTextManager       text;

    /// Overlay manager.
    KwOverlayManager    overlay;

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwDisplayManager(KwAbstractDisplay* display);

    /// Destructor.
    virtual ~KwDisplayManager();

  private:

    /*
     * Variables
     */

    /// Display object.
    KwDisplayMixer m_mixer;
};

#endif // _KwDisplayManager_h_

