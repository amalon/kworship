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

#ifndef _KwTextStyle_h_
#define _KwTextStyle_h_

/**
 * @file KwTextStyle.h
 * @brief Graphical text style information.
 * @author James Hogan <james@albanarts.com>
 */

#include <QFont>
#include <QBrush>
#include <QPen>

class KwCssScope;

/// Background text layer.
class KwTextStyle
{
  public:

    /*
     * Constructors + destructor.
     */

    /// Default constructor.
    KwTextStyle();

    /// Destructor.
    virtual ~KwTextStyle();

    /*
     * CSS Styles interface.
     */

    /// Load styles from scope.
    void loadFrom(KwCssScope* scope);

    /*
     * Variables
     */

    /// Character style
    struct Character
    {
      /// Font information.
      QFont font;

      /// Inner brush fill.
      QBrush brush;

      struct Outline
      {
        /// Whether to draw an outline around characters
        bool enabled;

        /// Outline pen.
        QPen pen;
      } outline;

      struct Shadow
      {
        /// Whether to shadow behind characters
        bool enabled;

        /// Shadow brush.
        QBrush brush;

        /// Shadow offset.
        int offset;
      } shadow;
    } character;

    /// Layout style
    struct Layout
    {
      /// Margins.
      struct Margins {
        float left, right, top, bottom;
      } margins;
    } layout;
};

#endif // _KwTextStyle_h_

