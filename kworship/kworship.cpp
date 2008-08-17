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


#include "kworship.h"
#include "kworshipview.h"
#include "settings.h"

#include "KwImageLayer.h"
#include "KwTextLayer.h"

#include <QtGui/QDropEvent>
#include <QtGui/QPainter>

#include <kconfigdialog.h>
#include <kstatusbar.h>

#include <kaction.h>
#include <kactioncollection.h>
#include <kstandardaction.h>

#include <KDE/KLocale>

kworship::kworship()
    : KXmlGuiWindow(),
      m_view(new kworshipView(this)),
      m_printer(0)
{
  
  m_mainDisplay = 0;
  m_previewDisplay = 0;
  
  // accept dnd
  setAcceptDrops(true);

  // tell the KXmlGuiWindow that this is indeed the main widget
  setCentralWidget(m_view);

  // then, setup our actions
  setupActions();

  // add a status bar
  statusBar()->show();

  // a call to KXmlGuiWindow::setupGUI() populates the GUI
  // with actions, using KXMLGUI.
  // It also applies the saved mainwindow settings, if any, and ask the
  // mainwindow to automatically save settings if changed: window size,
  // toolbar position, icon size, etc.
  setupGUI();

  addDockWidget(Qt::RightDockWidgetArea, m_view->dockWidget);
  addDockWidget(Qt::RightDockWidgetArea, m_view->dockWidget_2);
  addDockWidget(Qt::RightDockWidgetArea, m_view->dockWidget_3);
  addDockWidget(Qt::RightDockWidgetArea, m_view->dockWidget_4);
  addDockWidget(Qt::RightDockWidgetArea, m_view->dockWidget_5);

  if (true)
  {
    // Initialise the display to a background image
    unsigned int count = 0;
    if (0)
    {
      KwImageLayer* background = new KwImageLayer(QPixmap("/home/james/media/images/projector/pmdata/Backgrounds/A15.JPG"));
      m_displayController.setLayer(count++, background, true);
    }

    // Initialise the display to a background image
    {
      KwImageLayer* background = new KwImageLayer(QPixmap("/home/james/media/images/projector/misc/love-god-light.jpg"));
      m_displayController.setLayer(count++, background, true);
    }

    // And some text
    KwTextLayer* lyrics = new KwTextLayer("Wipidy-doo-dah, Yipidy-ay!\nMy oh my what a wonderful day!");
    m_displayController.setLayer(count++, lyrics, true);
  }

  m_previewDisplay = new KwLocalDisplayPreview;
  m_view->verticalLayout_5->addWidget(m_previewDisplay);
  m_displayController.attachChild(m_previewDisplay);
}

kworship::~kworship()
{
}

void kworship::setupActions()
{
    KStandardAction::openNew(this, SLOT(fileNew()), actionCollection());
    KStandardAction::quit(qApp, SLOT(quit()), actionCollection());

    KStandardAction::preferences(this, SLOT(optionsPreferences()), actionCollection());

    // custom menu and menu item - the slot is in the class kworshipView
    KAction *custom = new KAction(KIcon("colorize"), i18n("Swi&tch Colors"), this);
    actionCollection()->addAction( QLatin1String("switch_action"), custom );
    connect(custom, SIGNAL(triggered(bool)), m_view, SLOT(switchColors()));
}

void kworship::fileNew()
{
  // this slot is called whenever the File->New menu is selected,
  // the New shortcut is pressed (usually CTRL+N) or the New toolbar
  // button is clicked

  // create a new window
  //(new kworship)->show();
  bool newlyCreated = (0 == m_mainDisplay);
  if (newlyCreated)
  {
    m_mainDisplay = new KwLocalDisplayPreview;
    m_mainDisplay->setPrimary(true);
    m_displayController.attachChild(m_mainDisplay);
  }
  m_mainDisplay->showFullScreen();
//  m_mainDisplay->show();
}

void kworship::optionsPreferences()
{
    // The preference dialog is derived from prefs_base.ui
    //
    // compare the names of the widgets in the .ui file
    // to the names of the variables in the .kcfg file
    //avoid to have 2 dialogs shown
    if ( KConfigDialog::showDialog( "settings" ) )  {
        return;
    }
    KConfigDialog *dialog = new KConfigDialog(this, "settings", Settings::self());
    QWidget *generalSettingsDlg = new QWidget;
    ui_prefs_base.setupUi(generalSettingsDlg);
    dialog->addPage(generalSettingsDlg, i18n("General"), "package_setting");
    connect(dialog, SIGNAL(settingsChanged(QString)), m_view, SLOT(settingsChanged()));
    dialog->setAttribute( Qt::WA_DeleteOnClose );
    dialog->show();
}

#include "kworship.moc"
