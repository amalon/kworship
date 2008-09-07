#ifndef _KwCssStyles_h_
#define _KwCssStyles_h_

/**
 * @file KwCssStyles.h
 * @brief Set of cascading style properties.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssStyle.h"

#include <QHash>

class KwCssAbstractStyle;
class KwCssStyleStates;

/// Set of cascading style properties.
class KwCssStyles
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwCssStyles();

    /// Copy constructor.
    KwCssStyles(const KwCssStyles& other);

    /// Destructor.
    virtual ~KwCssStyles();

    /*
     * Main interface
     */

    /// Set a style.
    void setRawStyle(QString name, KwCssAbstractStyle* style);

    /// Set a style of a particular type.
    template <typename T>
    void setStyle(QString name, const T& value)
    {
      setRawStyle(name, new KwCssStyle<T>(value));
    }

    /*
     * Operators
     */

    /// Apply styles to states.
    friend KwCssStyleStates& operator << (KwCssStyleStates& states, const KwCssStyles& styles);

  private:

    /*
     * Types
     */

    /// Dictionary of strings to styles.
    typedef QHash<QString, KwCssAbstractStyle*> StyleDictionary;

    /*
     * Variables
     */

    /// The style properties.
    StyleDictionary m_styles;

};

#endif // _KwCssStyles_h_

