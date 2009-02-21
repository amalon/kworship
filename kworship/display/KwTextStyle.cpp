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

/**
 * @file KwTextStyle.cpp
 * @brief Graphical text style information.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwTextStyle.h"
#include "KwDisplayStyles.h"

/*
 * Constructors + destructor.
 */

/// Default constructor.
KwTextStyle::KwTextStyle()
{
  character.outline.enabled = false;
  character.shadow.enabled = false;
  character.shadow.offset = 5;
  layout.margins.left = 0.05f;
  layout.margins.right = 0.05f;
  layout.margins.top = 0.05f;
  layout.margins.bottom = 0.05f;
}

/// Destructor.
KwTextStyle::~KwTextStyle()
{
}

/*
 * CSS Styles interface.
 */

/// Load styles from scope.
void KwTextStyle::loadFrom(KwCssScope* scope)
{
#define GETSTYLE(A,B) A = KwDisplayStyles::text::B(scope)
#define GETSTYLE1(A1) GETSTYLE(A1, A1)
#define GETSTYLE2(A1,A2) GETSTYLE(A1.A2, A1::A2)
#define GETSTYLE3(A1,A2,A3) GETSTYLE(A1.A2.A3, A1::A2::A3)

  GETSTYLE2(character, font);
  GETSTYLE2(character, brush);
  GETSTYLE3(character, outline, enabled);
  GETSTYLE3(character, outline, pen);
  GETSTYLE3(character, shadow, enabled);
  GETSTYLE3(character, shadow, brush);
  GETSTYLE3(character, shadow, offset);
  //GETSTYLE2(layout, alignment);
  GETSTYLE3(layout, margins, left);
  GETSTYLE3(layout, margins, right);
  GETSTYLE3(layout, margins, top);
  GETSTYLE3(layout, margins, bottom);
}
