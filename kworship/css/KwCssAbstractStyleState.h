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

