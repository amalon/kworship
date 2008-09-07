#ifndef _KwTextManager_h_
#define _KwTextManager_h_

/**
 * @file KwTextManager.h
 * @brief Text manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractDisplayManager.h"

#include <QString>

class KwCssScope;

/// Text manager.
/**
 * High level interface for controlling text on screen.
 */
class KwTextManager : public KwAbstractDisplayManager
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwTextManager();

    /// Destructor.
    virtual ~KwTextManager();

    /*
     * Main interface
     */

    /// Apply the styles in a scope.
    void applyStyles(KwCssScope* scope);

    /// Clear all text.
    void clear();

    /// Set the text.
    void setText(QString text);
};

#endif // _KwTextManager_h_

