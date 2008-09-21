/***************************************************************************
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   This file is part of KWorship.                                        *
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

