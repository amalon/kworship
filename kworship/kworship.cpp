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
#include "KwDisplayManager.h"

#include "KwLocalDisplayPreview.h"
#include "KwPlaylistList.h"
#include "KwPlaylistNote.h"
#include "KwPlaylistText.h"
#include "KwPlaylistImage.h"
#include "KwPlaylistVideo.h"
#include "KwPlaylistModel.h"


#include <QtGui/QDropEvent>
#include <QtGui/QPainter>

#include <kconfigdialog.h>
#include <kstatusbar.h>

#include <kaction.h>
#include <kactioncollection.h>
#include <kstandardaction.h>

#include <KDE/KLocale>

kworship::kworship()
: KXmlGuiWindow()
, m_view(new kworshipView(this))
, m_displayManager(0)
, m_printer(0)
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

  // Setup the dockers
  addDockWidget(Qt::LeftDockWidgetArea, m_view->dockPresentation);
  tabifyDockWidget(m_view->dockPresentation, m_view->dockBible);
  tabifyDockWidget(m_view->dockPresentation, m_view->dockSongs);
  addDockWidget(Qt::RightDockWidgetArea, m_view->dockPreview);
  addDockWidget(Qt::RightDockWidgetArea, m_view->dockLyrics);
  addDockWidget(Qt::BottomDockWidgetArea, m_view->dockThemes);

  // Setup some stuff in the tree
#if 0
#define TREE_ITEM(name, string, parent) QTreeWidgetItem* name = new QTreeWidgetItem(parent); name->setText(0, tr(string));

  TREE_ITEM(song1, "Our God is a great big God", m_view->treeWidget);
  TREE_ITEM(song1_style, "(style)", song1);
  TREE_ITEM(song1_style_1, "Mode", song1_style);
  TREE_ITEM(song1_v1, "Our God is a great big God,\nOur God is a great big God,\nOur God is a great big God,\nAnd He holds us in his hands.", song1);
  TREE_ITEM(song1_v2, "He's higher than a skyscraper\nAnd he's deeper than a submarine.", song1);
  TREE_ITEM(song1_v3, "He's wider than the universe\nAnd beyond my wildest dreams.", song1);

#undef TREE_ITEM
#endif

  // Playlist
  m_primaryPlaylist = new KwPlaylistList();
  m_primaryPlaylist->addItem(new KwPlaylistNote("This is a note #1a#"));
  m_primaryPlaylist->addItem(new KwPlaylistNote("This is a note #2a#"));
  m_primaryPlaylist->addItem(new KwPlaylistNote("This is a note #3a#"));

  KwPlaylistItem* song;
  m_primaryPlaylist->addItem(song = new KwPlaylistText("Our God is a great big God", QStringList()
    << "Our God is a great big God,\nOur God is a great big God,\nOur God is a great big God,\nAnd He holds us in his hands."
    << "He's higher than a skyscraper\nAnd he's deeper than a submarine.\nHe's wider than the universe\nAnd beyond my wildest dreams."
    << "And He's known me and He's loved me\nSince before the world began.\nHow wonderful\nto be a part\nof God's amazing plan"
  ));

  KwPlaylistList* list1 = new KwPlaylistList();
  m_primaryPlaylist->addItem(list1);
  list1->addItem(new KwPlaylistNote("This is a note #1b"));
  list1->addItem(new KwPlaylistNote("This is a note #2b"));
  list1->addItem(new KwPlaylistNote("This is a note #3b"));

  m_primaryPlaylist->addItem(new KwPlaylistImage("/home/james/media/images/projector/misc/love-god-light.jpg"));
  m_primaryPlaylist->addItem(new KwPlaylistVideo("/home/james/YouTube/songs/great_big_god.flv"));

  m_playlistModel = new KwPlaylistModel;
  m_playlistModel->setRootNode(m_primaryPlaylist->getNode(0));
  m_view->treePlaylist->setModel(m_playlistModel);
  m_view->treePlaylist->setExpandsOnDoubleClick(false);

  m_displayManager = new KwDisplayManager(&m_displayController);

  m_previewDisplay = new KwLocalDisplayPreview;
  m_view->layoutPreview->addWidget(m_previewDisplay);
  m_displayController.attachChild(m_previewDisplay);


  connect(m_view->treePlaylist, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(playlist_doubleClicked(QModelIndex)));
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
    //KAction *custom = new KAction(KIcon("colorize"), i18n("Swi&tch Colors"), this);
    //actionCollection()->addAction( QLatin1String("switch_action"), custom );
    //connect(custom, SIGNAL(triggered(bool)), m_view, SLOT(switchColors()));
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

void kworship::playlist_doubleClicked(QModelIndex index)
{
  KwPlaylistNode* node = m_playlistModel->itemFromIndex(index);
  node->activate(m_displayManager);
}

#include "kworship.moc"
