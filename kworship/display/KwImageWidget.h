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

#ifndef _KwImageWidget_h_
#define _KwImageWidget_h_

/**
 * @file KwImageWidget.h
 * @brief Background image widget.
 * @author James Hogan <james@albanarts.com>
 */

#include <QWidget>

/// Background image widget.
class KwImageWidget : public QWidget
{
  public:

    /*
     * Constructors + destructors
     */

    /// Primary constructor.
    KwImageWidget(QBrush brush);

    /// Primary constructor.
    KwImageWidget(const QPixmap& pixmap, bool stretch, bool keepAspect);

    /// Primary constructor.
    KwImageWidget(QBrush brush, const QPixmap& pixmap, bool stretch, bool keepAspect);

    /// Destructor.
    virtual ~KwImageWidget();

  protected:

    /*
     * Events
     */

    /// Repaint evemt.
    void paintEvent(QPaintEvent* e);

  private:

    /*
     * Variables
     */

    /// Background brush.
    QBrush m_brush;

    /// Pixmap image.
    QPixmap m_pixmap;

    /// Whether to stretch the image to fit the screen.
    bool m_stretch;

    /// Whether to keep the aspect ratio of the image.
    bool m_keepAspect;
};

#endif // _KwImageWidget_h_

