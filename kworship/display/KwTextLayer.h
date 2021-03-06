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

#ifndef _KwTextLayer_h_
#define _KwTextLayer_h_

/**
 * @file KwTextLayer.h
 * @brief Layer of pretty text.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractLayer.h"
#include "KwTextStyle.h"

#include <QSize>
#include <QPixmap>

/// Layer of pretty text.
class KwTextLayer : public KwAbstractLayer
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwTextLayer();

    /// Primaryt constructor.
    KwTextLayer(QString text, bool formatted = false);

    /// Destructor.
    virtual ~KwTextLayer();

    /*
     * Mutators
     */

    /// Set text styles.
    void setStyle(const KwTextStyle& style);

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

    /// Text style.
    KwTextStyle m_style;

    /// The actual text.
    QString m_text;

    /// Whether the text is formatted.
    bool m_formatted;
};

#endif // _KwTextLayer_h_

