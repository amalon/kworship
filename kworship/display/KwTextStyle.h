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

/// Background text layer.
class KwTextStyle
{
  public:

    /*
     * Variables
     */

    /// Font information.
    QFont font;

    /// Inner brush fill.
    QBrush innerBrush;

    /// Outline pen.
    QPen ountlinePen;

    /// Shadow brush.
    QBrush shadowBrush;
};

#endif // _KwTextStyle_h_

