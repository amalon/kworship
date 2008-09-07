#ifndef _KwCssAbstractStyle_h_
#define _KwCssAbstractStyle_h_

/**
 * @file KwCssAbstractStyle.h
 * @brief Abstract cascading style property.
 * @author James Hogan <james@albanarts.com>
 */

class KwCssAbstractStyle;
class KwCssAbstractStyleState;

/// Abstract cascading style property.
class KwCssAbstractStyle
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwCssAbstractStyle();

    /// Destructor.
    virtual ~KwCssAbstractStyle();

    /*
     * Main interface
     */

    /// Get a new state.
    virtual KwCssAbstractStyleState* getNewState() const = 0;

    /// Duplicate this style.
    virtual KwCssAbstractStyle* duplicate() const = 0;

};

#endif // _KwCssAbstractStyle_h_

