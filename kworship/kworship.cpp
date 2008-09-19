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
#include "prefsDisplay.h"

#include "KwPlaylistNode.h"
#include "KwPlaylistList.h"
#include "KwPlaylistNote.h"
#include "KwPlaylistText.h"
#include "KwPlaylistImage.h"
#include "KwPlaylistVideo.h"
#include "KwPlaylistModel.h"

#include "KwCssStyleSheet.h"
#include "KwCssStyleRule.h"

#include "KwDisplayManager.h"
#include "KwLocalDisplay.h"
#include "KwLocalDisplayPreview.h"

#include "KwMediaManager.h"
#include "KwMediaControlWidget.h"

#include "KwSongdbModel.h"
#include "KwSongdbFilterNode.h"
#include "KwSongdbTree.h"

#include <kconfigdialog.h>
#include <kstatusbar.h>
#include <kaction.h>
#include <kactionmenu.h>
#include <kmenu.h>
#include <ktoggleaction.h>
#include <kactioncollection.h>
#include <kstandardaction.h>
#include <KDE/KLocale>

#include <phonon/audiooutput.h>

#include <QtGui/QDropEvent>
#include <QtGui/QPainter>
#include <QColor>
#include <QDesktopWidget>
#include <QToolBar>
#include <QToolButton>
#include <QSqlDatabase>

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
  addDockWidget(Qt::BottomDockWidgetArea, m_view->dockNowPlaying);

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

  KwCssStyleSheet* styleRules = new KwCssStyleSheet;

  KwCssStyleRule beachyTheme;
  beachyTheme.setCriteriaClasses(QSet<QString>() << "beachy");
  beachyTheme.setStyle<QBrush>("background.brush", Qt::black);
  beachyTheme.setStyle<QPixmap>("background.image.pixmap", QPixmap("/home/james/media/images/projector/misc/love-god-light.jpg"));
  styleRules->addRule(beachyTheme);

  m_primaryPlaylist->addStyleSheet(styleRules);

  KwPlaylistItem* song;
  m_primaryPlaylist->addItem(song = new KwPlaylistText("Our God is a great big God", QStringList()
    << "Our God is a great big God,\nOur God is a great big God,\nOur God is a great big God,\nAnd He holds us in his hands."
    << "He's higher than a skyscraper\nAnd he's deeper than a submarine.\nHe's wider than the universe\nAnd beyond my wildest dreams."
    << "And He's known me and He's loved me\nSince before the world began.\nHow wonderful\nto be a part\nof God's amazing plan"
  ));
  song->addClass("beachy");

  KwPlaylistList* list1 = new KwPlaylistList();
  m_primaryPlaylist->addItem(list1);
  list1->addItem(new KwPlaylistNote("This is a note #1b"));
  list1->addItem(new KwPlaylistNote("This is a note #2b"));
  list1->addItem(new KwPlaylistNote("This is a note #3b"));

  m_primaryPlaylist->addItem(new KwPlaylistImage("/home/james/media/images/projector/misc/love-god-light.jpg"));
  m_primaryPlaylist->addItem(new KwPlaylistVideo("/home/james/YouTube/songs/great_big_god.flv"));
  m_primaryPlaylist->addItem(new KwPlaylistVideo("/home/james/YouTube/songs/Hillsong_Kidz_Rainbow.flv"));

  m_playlistModel = new KwPlaylistModel;
  m_playlistModel->setRootNode(m_primaryPlaylist->getNode(0));
  m_view->treePlaylist->setModel(m_playlistModel);
  m_view->treePlaylist->setExpandsOnDoubleClick(false);
  m_view->treePlaylist->setAcceptDrops(true);

  connect(m_view->treePlaylist, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(playlist_doubleClicked(QModelIndex)));

  m_mediaManager = new KwMediaManager();
  m_mediaManager->linkAudio(new Phonon::AudioOutput(Phonon::MusicCategory));
  m_displayManager = new KwDisplayManager(&m_displayController, m_mediaManager);

  m_previewDisplay = new KwLocalDisplayPreview;
  m_view->layoutPreview->addWidget(m_previewDisplay);
  m_displayController.attachChild(m_previewDisplay);

  KwMediaControlWidget* mediaWidget = new KwMediaControlWidget(m_mediaManager, m_view->dockNowPlaying);
  m_view->layoutNowPlaying->addWidget(mediaWidget);

  QToolBar* songToolBar = new QToolBar("Songs");
  m_view->layoutSongsToolbar->layout()->addWidget(songToolBar);

  KActionMenu* groupByAction = new KActionMenu(KIcon("ogg"), "Group By", songToolBar);
  groupByAction->setDelayed(false);
  songToolBar->addAction(groupByAction);

  KMenu* groupByMenu = new KMenu(songToolBar);
  groupByAction->setMenu(groupByMenu);

  // Setup song db
  QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
  db.setHostName("localhost");
  db.setDatabaseName("kworship");
  db.setUserName("root");
  bool ok = db.open();
  assert(ok);

  KwSongdbTree* treeView = new KwSongdbTree(m_view);
  m_view->layoutSongsTree->addWidget(treeView);
  groupByMenu->addActions(treeView->groupByActions()->actions());

  // Show the display on startup?
  if (Settings::displayShowStartup())
  {
    toggleMainDisplay(true);
    m_mainDisplayAction->setChecked(true);
  }
}

kworship::~kworship()
{
}

void kworship::setupActions()
{
  // Application
  KStandardAction::quit(qApp, SLOT(quit()), actionCollection());
  KStandardAction::preferences(this, SLOT(optionsPreferences()), actionCollection());

  // File management
  KStandardAction::openNew(this, SLOT(fileNew()), actionCollection());
  KStandardAction::open(this, SLOT(fileOpen()), actionCollection());
  KStandardAction::save(this, SLOT(fileSave()), actionCollection());
  KStandardAction::saveAs(this, SLOT(fileSaveAs()), actionCollection());

  // Display
  KStandardAction::fullScreen(this, SLOT(toggleFullscreen(bool)), this, actionCollection());
  {
    m_mainDisplayAction = new KToggleAction(KIcon("colorize"), i18n("Show Main Display"), this);
    actionCollection()->addAction( QLatin1String("show_main_display"), m_mainDisplayAction );
    connect(m_mainDisplayAction, SIGNAL(triggered(bool)), this, SLOT(toggleMainDisplay(bool)));
  }
  {
    KAction* clearDisplayAction = new KAction(KIcon("clear"), i18n("Clear display"), this);
    actionCollection()->addAction( QLatin1String("display_clear"), clearDisplayAction);
    connect(clearDisplayAction, SIGNAL(triggered()), this, SLOT(displayClear()));
  }
}

void kworship::settingsChanged()
{
  // If the main display is on and screen has changed, move it now
  if (0 != m_mainDisplay && getCorrectDisplayScreen() != getCurrentDisplayScreen())
  {
    toggleMainDisplay(false);
    toggleMainDisplay(true);
    m_mainDisplayAction->setChecked(true);
  }
}

int kworship::getCorrectDisplayScreen()
{
  QDesktopWidget* desktop = qobject_cast<QApplication*>(QCoreApplication::instance())->desktop();
  assert(0 != desktop);

  int screens = desktop->numScreens();
  int displayScreen = -1;
  if (Settings::displayScreenChoose())
  {
    displayScreen = Settings::displayScreen();
  }
  if (-1 == displayScreen)
  {
    int currentScreen;
    if (m_view->isVisible())
    {
      currentScreen = desktop->screenNumber(m_view);
    }
    else
    {
      currentScreen = desktop->primaryScreen();
    }
    displayScreen = 0;
    if (displayScreen == currentScreen && displayScreen < screens-1)
    {
      ++displayScreen;
    }
  }

  return displayScreen;
}

int kworship::getCurrentDisplayScreen()
{
  QDesktopWidget* desktop = qobject_cast<QApplication*>(QCoreApplication::instance())->desktop();
  assert(0 != desktop);

  int previousScreen = desktop->screenNumber(m_mainDisplay);

  return previousScreen;
}

void kworship::toggleMainDisplay(bool checked)
{
  if (checked)
  {
    // Ensure the display exists
    if (0 == m_mainDisplay)
    {
      m_mainDisplay = new KwLocalDisplay;
      m_mainDisplay->setPrimary(true);
      m_displayController.attachChild(m_mainDisplay);
      connect(m_mainDisplay, SIGNAL(closed()), this, SLOT(mainDisplayClosed()));
    }

    QDesktopWidget* desktop = qobject_cast<QApplication*>(QCoreApplication::instance())->desktop();
    assert(0 != desktop);

    int previousScreen = getCurrentDisplayScreen();
    int screens = desktop->numScreens();
    int displayScreen = getCorrectDisplayScreen();

    if (displayScreen >= 0 && displayScreen < screens)
    {
      m_mainDisplay->move(desktop->screenGeometry(displayScreen).topLeft());
    }

    m_mainDisplay->showFullScreen();
  }
  else
  {
    if (0 != m_mainDisplay)
    {
      m_mainDisplay->close();
    }
  }
}

void kworship::mainDisplayClosed()
{
  m_mainDisplay->deleteLater();
  m_mainDisplay = 0;
  m_mainDisplayAction->setChecked(false);
}

void kworship::displayClear()
{
  m_displayManager->background.clear();
  m_displayManager->text.clear();
}

void kworship::toggleFullscreen(bool checked)
{
  if (checked)
  {
    showFullScreen();
  }
  else
  {
    showNormal();
  }
}

void kworship::fileNew()
{
}

void kworship::fileOpen()
{
}

void kworship::fileSave()
{
}

void kworship::fileSaveAs()
{
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

  QWidget *generalSettingsDlg = new QWidget(dialog);
  ui_prefs_base.setupUi(generalSettingsDlg);
  dialog->addPage(generalSettingsDlg, i18n("General"), "package_setting");

  prefsDisplay *displaySettingsDlg = new prefsDisplay(dialog);
  dialog->addPage(displaySettingsDlg, i18n("Display"), "display_setting");

  QWidget *songdbSettingsDlg = new QWidget;
  //ui_prefsSongdb_base.setupUi(songdbSettingsDlg);
  dialog->addPage(songdbSettingsDlg, i18n("Song DB"), "songdb_setting");

  connect(dialog, SIGNAL(settingsChanged(QString)), m_view, SLOT(settingsChanged()));
  connect(dialog, SIGNAL(settingsChanged(QString)), this, SLOT(settingsChanged()));
  dialog->setAttribute( Qt::WA_DeleteOnClose );
  dialog->show();
}

void kworship::playlist_doubleClicked(QModelIndex index)
{
  KwPlaylistNode* node = m_playlistModel->itemFromIndex(index);
  node->activate(m_displayManager);
}

#include "kworship.moc"
