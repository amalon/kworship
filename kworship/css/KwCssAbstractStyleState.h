#ifndef _KwCssAbstractStyleState_h_
#define _KwCssAbstractStyleState_h_

/**
 * @file KwCssAbstractStyleState.h
 * @brief Abstract state of cascading style property.
 * @author James Hogan <james@albanarts.com>
 */

class KwCssAbstractStyle;

/// Abstract state of cascading style property.
class KwCssAbstractStyleState
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwCssAbstractStyleState();

    /// Destructor.
    virtual ~KwCssAbstractStyleState();

    /*
     * Main interface
     */

    /// Create a new style for this state.
    virtual KwCssAbstractStyle* createStyle() const = 0;

    /*
     * Operators
     */

    /// Apply the style to this state.
    virtual KwCssAbstractStyleState& operator << (const KwCssAbstractStyle* style) = 0;

    /// Duplicate this style.
    virtual KwCssAbstractStyleState* duplicate() const = 0;

};

#endif // _KwCssAbstractStyleState_h_

