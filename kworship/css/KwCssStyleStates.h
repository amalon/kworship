#ifndef _KwCssStyleStates_h_
#define _KwCssStyleStates_h_

/**
 * @file KwCssStyleStates.h
 * @brief Set of cascading style property states.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssStyle.h"

#include <QHash>

#include <cassert>

class KwCssAbstractStyleState;

/// Set of cascading style properties.
class KwCssStyleStates
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwCssStyleStates();

    /// Copy constructor.
    KwCssStyleStates(const KwCssStyleStates& other);

    /// Destructor.
    virtual ~KwCssStyleStates();

    /*
     * Main interface
     */

    /// Clear all states.
    void clear();

    /// Get a state.
    const KwCssAbstractStyleState* getRawStyle(QString name) const;

    /// Get the value of a state.
    template <typename T>
    T getStyle(QString name) const
    {
      const KwCssAbstractStyleState* rawStyle = getRawStyle(name);
      if (0 != rawStyle)
      {
        const KwCssStyleState<T>* style = dynamic_cast<const KwCssStyleState<T>*>(rawStyle);
        assert(0 != style &&"style with incorrect type");
        if (0 != style)
        {
          return style->getValue();
        }
      }
      return T();
    }

    /*
     * Operators
     */

    /// Copy assignment operator.
    KwCssStyleStates& operator = (const KwCssStyleStates& other);

    /// Index into styles mapping.
    KwCssAbstractStyleState*& operator [] (QString name);

  private:

    /*
     * Types
     */

    /// Dictionary of strings to styles.
    typedef QHash<QString, KwCssAbstractStyleState*> StyleStateDictionary;

    /*
     * Variables
     */

    /// The style properties.
    StyleStateDictionary m_styleStates;

};

#endif // _KwCssStyleStates_h_

