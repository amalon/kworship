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

#ifndef _KwCssStyle_h_
#define _KwCssStyle_h_

/**
 * @file KwCssStyle.h
 * @brief Typed cascading style property.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssAbstractStyle.h"
#include "KwCssUnprocessed.h"

#include <kdemacros.h>

/// Stringify a type.
template <typename T>
KDE_EXPORT KwCssUnprocessed KwCssStringify(const T& value);

/// Unstringify a type.
template <typename T>
KDE_EXPORT T KwCssUnstringify(const KwCssUnprocessed& value, bool* success);

/// Typed cascading style property.
/**
 * @param T The type of the property.
 */
template <typename T>
class KDE_EXPORT KwCssStyle : public KwCssAbstractStyle
{
  public:

    /*
     * Types
     */

    /// Operation types.
    enum Operation
    {
      none,
      override,
      revert,
      clear
    };

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwCssStyle()
    : KwCssAbstractStyle()
    , m_operation(none)
    , m_value()
    {
    }

    /// Copy constructor.
    KwCssStyle(const KwCssStyle& copy)
    : KwCssAbstractStyle(copy)
    , m_operation(copy.m_operation)
    , m_value(copy.m_value)
    {
    }

    /// Primary constructor.
    KwCssStyle(const T& value, Operation op = override)
    : KwCssAbstractStyle()
    , m_operation(op)
    , m_value(value)
    {
    }

    /// Primary constructor.
    KwCssStyle(Operation op)
    : KwCssAbstractStyle()
    , m_operation(op)
    , m_value()
    {
    }

    /// Destructor.
    virtual ~KwCssStyle()
    {
    }

    /*
     * Main interface
     */

    // Reimplemented
    virtual KwCssAbstractStyleState* getNewState() const;

    // Reimplemented
    virtual KwCssAbstractStyle* duplicate() const
    {
      return new KwCssStyle<T>(*this);
    }

    // Reimplemented
    virtual QString toString() const
    {
      switch (m_operation)
      {
        case revert:
          {
            return "revert";
          }

        case override:
          {
            return KwCssStringify(m_value);
          }

        case clear:
          {
            return "clear";
          }

        case none:
        default:
          {
            return "inherit";
          }

      }
    }

    /*
     * Accessors
     */

    /// Get the operation type.
    Operation getOperation() const
    {
      return m_operation;
    }

    /// Get the value.
    T getValue() const
    {
      return m_value;
    }
    
  private:

    /*
     * Variables
     */

    /// Type of operation.
    Operation m_operation;

    /// Initial or overrided value.
    T m_value;
};

/// Construct a style of some type from an unprocessed string.
template <typename T>
KwCssAbstractStyle* KwCssConstruct(const KwCssUnprocessed& value)
{
  bool worked;
  T val = KwCssUnstringify<T>(value, &worked);
  if (worked)
  {
    return new KwCssStyle<T>(val);
  }
  else
  {
    return 0;
  }
}

#include "KwCssStyleState.h"

/// Get a new state.
template <typename T>
KwCssAbstractStyleState* KwCssStyle<T>::getNewState() const
{
  return new KwCssStyleState<T>();
}

#endif // _KwCssStyle_h_

