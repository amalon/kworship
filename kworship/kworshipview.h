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

#ifndef kworshipVIEW_H
#define kworshipVIEW_H

#include <QtGui/QWidget>

#include "ui_kworshipview_base.h"

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

class kworshipView : public QWidget, public Ui::kworshipview_base
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    kworshipView(QWidget *parent);

    /**
     * Destructor
     */
    virtual ~kworshipView();

signals:
    /**
     * Use this signal to change the content of the statusbar
     */
    void signalChangeStatusbar(const QString& text);

    /**
     * Use this signal to change the content of the caption
     */
    void signalChangeCaption(const QString& text);

private slots:
    void settingsChanged();
};

#endif // kworshipVIEW_H
