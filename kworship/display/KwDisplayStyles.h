#ifndef _KwDisplayStyles_h_
#define _KwDisplayStyles_h_

/**
 * @file KwDisplayStyles.h
 * @brief Display styles interface.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssStandardise.h"

#include <QString>
#include <QBrush>
#include <QFont>
#include <QPen>

namespace KwDisplayStyles
{
  // Display background
  KWCSS_ROOT_NAMESPACE(background)
    // Brush to fill the background
    KWCSS_DEFINE_PROPERTY(QBrush, brush)
    // Image backgrounds
    KWCSS_START_NAMESPACE(background, image)
      // Pixmap to display
      KWCSS_DEFINE_PROPERTY(QPixmap, pixmap)
    KWCSS_END_NAMESPACE()
    // Video backgrounds
    KWCSS_START_NAMESPACE(background, video)
      // Path of video file
      KWCSS_DEFINE_PROPERTY(QString, path)
      // Whether to loop the video
      KWCSS_DEFINE_PROPERTY(bool, loop)
    KWCSS_END_NAMESPACE()
  KWCSS_END_NAMESPACE()

  // Text
  KWCSS_ROOT_NAMESPACE(text)
    // Font display settings
    KWCSS_START_NAMESPACE(text, font)
      KWCSS_DEFINE_PROPERTY(QFont, font)
      KWCSS_DEFINE_PROPERTY(QBrush, brush)
      KWCSS_START_NAMESPACE(text.font, outline)
        KWCSS_DEFINE_PROPERTY(bool, enabled)
        KWCSS_DEFINE_PROPERTY(QPen, pen)
      KWCSS_END_NAMESPACE()
      KWCSS_START_NAMESPACE(text.font, shadow)
        KWCSS_DEFINE_PROPERTY(bool, enabled)
      KWCSS_END_NAMESPACE()
    KWCSS_END_NAMESPACE()
    // Text layout settings
  KWCSS_END_NAMESPACE()
}

#endif // _KwDisplayStyles_h_

