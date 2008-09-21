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

#ifndef _KwImageLayer_h_
#define _KwImageLayer_h_

/**
 * @file KwImageLayer.h
 * @brief Background image layer.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractLayer.h"

#include <QSize>
#include <QBrush>
#include <QPixmap>

/// Background image layer.
class KwImageLayer : public KwAbstractLayer
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwImageLayer();

    /// Primary constructor.
    KwImageLayer(QBrush brush);

    /// Primary constructor.
    KwImageLayer(const QPixmap& pixmap);

    /// Destructor.
    virtual ~KwImageLayer();

    /*
     * Methods
     */

    /// @copydoc KwAbstractLayer::addWidgets(QWidget*) const
    virtual void* addWidgets(QWidget* master) const;

    /// @copydoc KwAbstractLayer::removeWidgets(QWidget*,void*) const
    virtual void removeWidgets(QWidget* master, void* data) const;

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

#endif // _KwImageLayer_h_

