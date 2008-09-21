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

#include "prefsDisplay.h"
#include "DesktopView.h"
#include "settings.h"

/**
 * Default constructor
 */
prefsDisplay::prefsDisplay(QWidget *parent)
: QWidget(parent)
, Ui::prefsDisplay_base()
, m_desktopRect()
{
  setupUi(this);

  DesktopView* desktopView = new DesktopView(this);
  desktopView->setObjectName("kcfg_displayScreen");
  connect(desktopView, SIGNAL(screenSelected(int, bool)), this, SLOT(screenSelect(int, bool)));
  connect(desktopView, SIGNAL(statusChanged(QString)), labelStatus, SLOT(setText(QString)));
  layoutScreens->addWidget(desktopView);

  connect(kcfg_displayScreenChoose, SIGNAL(toggled(bool)), desktopView, SLOT(setEnabled(bool)));
}

/**
 * Destructor
 */
prefsDisplay::~prefsDisplay()
{
}

/// Indicates that a screen selection has changed.
void prefsDisplay::screenSelect(int screen, bool selected)
{
  Q_UNUSED(screen)
  Q_UNUSED(selected)
}

