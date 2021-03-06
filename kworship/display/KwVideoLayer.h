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

#ifndef _KwVideoLayer_h_
#define _KwVideoLayer_h_

/**
 * @file KwVideoLayer.h
 * @brief Background video layer.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractLayer.h"

#include <QSize>
#include <QPixmap>

class KwMediaManager;

/// Background video layer.
class KwVideoLayer : public KwAbstractLayer
{
  public:

    /*
     * Constructors + destructors
     */

    /// Primary constructor.
    KwVideoLayer(KwMediaManager* media);

    /// Destructor.
    virtual ~KwVideoLayer();

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

    /// Media manager.
    KwMediaManager* m_mediaManager;

    /// Whether to stretch the video to fit the screen.
    bool m_stretch;

    /// Whether to keep the aspect ratio of the video.
    bool m_keepAspect;
};

#endif // _KwVideoLayer_h_

