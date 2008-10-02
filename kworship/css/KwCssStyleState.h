/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   KWorship is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   KWorship is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with KWorship.  If not, write to the Free Software Foundation,  *
 *   Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.   *
 ***************************************************************************/

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

