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

#ifndef _KwMediaControlWidgetVisual_h_
#define _KwMediaControlWidgetVisual_h_

/**
 * @file KwMediaControlWidgetVisual.h
 * @brief Controls visual preferences of playing media items.
 * @author James Hogan <james@albanarts.com>
 */

#include <QWidget>

class KwMediaManager;

class QSlider;

/// Controls visual preferences of playing media items.
class KwMediaControlWidgetVisual : public QWidget
{
    Q_OBJECT
  public:

    /*
     * Constructors + destructors
     */

    /// Primary constructor.
    KwMediaControlWidgetVisual(KwMediaManager* manager, QWidget* parent);

    /// Destructor.
    virtual ~KwMediaControlWidgetVisual();

  public slots:

    /*
     * Public slots
     */

  signals:

    /*
     * Signals
     */

  private slots:

    /*
     * Private slots
     */

  private:

    /*
     * Variables
     */

    /// Manager to control.
    KwMediaManager* m_manager;
};

#endif // _KwMediaControlWidgetVisual_h_

