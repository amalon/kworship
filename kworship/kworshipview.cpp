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

#include "kworshipview.h"
#include "settings.h"

#include <klocale.h>
#include <QtGui/QLabel>

kworshipView::kworshipView(QWidget *)
{
    setupUi(this);
    settingsChanged();
    setAutoFillBackground(true);
}

kworshipView::~kworshipView()
{

}

void kworshipView::settingsChanged()
{
//     QPalette pal;
//     pal.setColor( QPalette::Window, Settings::col_background());
//     pal.setColor( QPalette::WindowText, Settings::col_foreground());
//     ui_kworshipview_base.kcfg_sillyLabel->setPalette( pal );
// 
//     // i18n : internationalization
//     ui_kworshipview_base.kcfg_sillyLabel->setText( i18n("This project is %1 days old",Settings::val_time()) );
//     emit signalChangeStatusbar( i18n("Settings changed") );
}

#include "kworshipview.moc"
