/***************************************************************************
 *   Copyright (C) 2008 by James Hogan   *
 *   james@albanarts.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef _prefsDisplay_h_
#define _prefsDisplay_h_

#include <QtGui/QWidget>

#include "ui_prefsDisplay_base.h"

class QPainter;
class KUrl;

/**
 * This is the main view class for kworship.  Most of the non-menu,
 * non-toolbar, and non-statusbar (e.g., non frame) GUI code should go
 * here.
 *
 * @short Main view
 * @author James Hogan <james@albanarts.com>
 * @version 0.1
 */

class prefsDisplay : public QWidget, public Ui::prefsDisplay_base
{
    Q_OBJECT
  public:
    /**
     * Default constructor
     */
    prefsDisplay(QWidget *parent);

    /**
     * Destructor
     */
    virtual ~prefsDisplay();

  private slots:

    /// Indicates that a screen selection has changed.
    void screenSelect(int screen, bool selected);

  private:
  
    /*
     * Variables
     */

    /// Desktop rectangle size.
    QRectF m_desktopRect;
};

#endif // _prefsDisplay_h_
