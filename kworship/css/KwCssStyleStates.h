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

