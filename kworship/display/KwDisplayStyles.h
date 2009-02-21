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

#ifndef _KwDisplayStyles_h_
#define _KwDisplayStyles_h_

/**
 * @file KwDisplayStyles.h
 * @brief Display styles interface.
 * @author James Hogan <james@albanarts.com>
 */

#include <KwCssStandardise.h>
#include <KwResourceLink.h>

#include <QFont>
#include <QBrush>
#include <QPen>

// The cpp file defines this to declare static variables
#ifdef KW_DISPLAY_STYLES_DECLARE
#undef KWCSS_EXTERN
#define KWCSS_EXTERN
#endif

namespace KwDisplayStyles
{
  // Define schema accessor
  KWCSS_SCHEMA

  // Display background
  KWCSS_ROOT_NAMESPACE(background)
    // Brush to fill the background
    KWCSS_DEFINE_PROPERTY(QBrush, brush)
    // Image backgrounds
    KWCSS_START_NAMESPACE(background, image)
      // Pixmap to display
      KWCSS_DEFINE_PROPERTY(KwResourceLink, src)
    KWCSS_END_NAMESPACE()
    /*
    // Video backgrounds
    KWCSS_START_NAMESPACE(background, video)
      // Path of video file
      KWCSS_DEFINE_PROPERTY(QString, path)
      // Whether to loop the video
      KWCSS_DEFINE_PROPERTY(bool, loop)
    KWCSS_END_NAMESPACE()
    */
  KWCSS_END_NAMESPACE()

  // Text
  KWCSS_ROOT_NAMESPACE(text)
    // Character styles
    KWCSS_START_NAMESPACE(text, character)
      KWCSS_DEFINE_PROPERTY(QFont, font)
      KWCSS_DEFINE_PROPERTY(QBrush, brush)
      KWCSS_START_NAMESPACE(text.character, outline)
        KWCSS_DEFINE_PROPERTY(bool, enabled)
        KWCSS_DEFINE_PROPERTY(QPen, pen)
      KWCSS_END_NAMESPACE()
      KWCSS_START_NAMESPACE(text.character, shadow)
        KWCSS_DEFINE_PROPERTY(bool, enabled)
        KWCSS_DEFINE_PROPERTY(QBrush, brush)
        KWCSS_DEFINE_PROPERTY(int, offset)
      KWCSS_END_NAMESPACE()
    KWCSS_END_NAMESPACE()
    // Text layout settings
    KWCSS_START_NAMESPACE(text, layout)
      //KWCSS_DEFINE_PROPERTY(int, alignment)
      KWCSS_START_NAMESPACE(text.layout, margins)
        KWCSS_DEFINE_PROPERTY(float, left)
        KWCSS_DEFINE_PROPERTY(float, right)
        KWCSS_DEFINE_PROPERTY(float, top)
        KWCSS_DEFINE_PROPERTY(float, bottom)
      KWCSS_END_NAMESPACE()
    KWCSS_END_NAMESPACE()
  KWCSS_END_NAMESPACE()
}

#endif // _KwDisplayStyles_h_

