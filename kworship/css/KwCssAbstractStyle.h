/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   KWorship is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   KWorship is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with KWorship.  If not, see <http://www.gnu.org/licenses/>.     *
 ***************************************************************************/

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

