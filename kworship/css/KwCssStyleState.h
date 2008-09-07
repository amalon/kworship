#ifndef _KwCssStyleState_h_
#define _KwCssStyleState_h_

/**
 * @file KwCssStyleState.h
 * @brief Typed cascading style property state.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssAbstractStyleState.h"
#include "KwCssStyle.h"

#include <QStack>

#include <cassert>

/// Typed cascading style property state.
/**
 * @param T The type of the property.
 */
template <typename T>
class KwCssStyleState : public KwCssAbstractStyleState
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwCssStyleState()
    : KwCssAbstractStyleState()
    , m_value()
    {
    }

    /// Copy constructor.
    KwCssStyleState(const KwCssStyleState& copy)
    : KwCssAbstractStyleState(copy)
    , m_value(copy.m_value)
    {
    }

    /// Destructor.
    virtual ~KwCssStyleState()
    {
    }

    /*
     * Main interface
     */

    /// Create a new style for this state.
    virtual KwCssAbstractStyle* createStyle() const
    {
      return new KwCssStyle<T>;
    }

    /// Duplicate this style.
    virtual KwCssAbstractStyleState* duplicate() const
    {
      return new KwCssStyleState<T>(*this);
    }

    T getValue() const
    {
      if (!m_value.empty())
      {
        return m_value.back();
      }
      else
      {
        return T();
      }
    }

    /*
     * Operators
     */

    /// Apply the style to this state.
    virtual KwCssAbstractStyleState& operator << (const KwCssAbstractStyle* style)
    {
      const KwCssStyle<T>* styleRetyped = dynamic_cast<const KwCssStyle<T>*>(style);
      assert(styleRetyped != 0 &&"Bad style type for this style state");

      switch (styleRetyped->getOperation())
      {
        case KwCssStyle<T>::override:
        {
          m_value.push_back(styleRetyped->getValue());
          break;
        }
        case KwCssStyle<T>::revert:
        {
          if (m_value.size() != 0)
          {
            m_value.pop_back();
          }
          break;
        }
        case KwCssStyle<T>::clear:
        {
          m_value.clear();
          break;
        }
        default:
        {
          // No change
          break;
        }
      }
      return *this;
    }

  private:

    /*
     * Variables
     */

    /// Stack of values.
    QStack<T> m_value;
};

#endif // _KwCssStyleState_h_

