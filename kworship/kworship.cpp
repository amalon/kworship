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

#include "kworship.h"
#include "kworshipview.h"
#include "settings.h"
#include "prefsDisplay.h"
#include "prefsSongDB.h"
#include "KwDatabaseSetup.h"

#include "KwPlaylistNode.h"
#include "KwPlaylistList.h"
#include "KwPlaylistNote.h"
#include "KwPlaylistText.h"
#include "KwPlaylistImage.h"
#include "KwPlaylistVideo.h"
#include "KwPlaylistPresentation.h"
#include "KwPlaylistModel.h"

#include "KwCssStyleSheet.h"
#include "KwCssStyleRule.h"

#include "KwDisplayManager.h"
#include "KwLocalDisplay.h"
#include "KwLocalDisplayPreview.h"

#include "KwMediaManager.h"
#include "KwMediaControlWidget.h"

#include "KwSongdb.h"
#include "KwSongdbModel.h"
#include "KwSongdbFilterNode.h"
#include "KwSongdbTree.h"

#include "UpManager.h"
#include "UpPresentationsModel.h"
#include "UpPresentation.h"
#include "UpPresentationNode.h"
#include "UpKpr1Backend.h"
#include "UpOoBackend.h"

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
#include <QComboBox>
#include <QSqlDatabase>
#include <QHeaderView>

kworship::kworship()
: KXmlGuiWindow()
, m_view(new kworshipView(this))
, m_displayManager(0)
, m_presentationManager(new UpManager(this))
, m_currentPresentation(0)
, m_printer(0)
{
  // set up presentation backends
  m_presentationManager->registerBackend<UpKpr1Backend>();
  m_presentationManager->registerBackend<UpOoBackend>();
  
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

  // Setup song db

  KwDatabaseSetup dbSetup;
  bool databaseOk = dbSetup.initialiseFromConfig();
  if (databaseOk)
  {
    new KwSongdb(dbSetup.database());
  }

  // Playlist
  m_primaryPlaylist = new KwPlaylistList();
  m_primaryPlaylist->addClass("beachy");

  KwCssStyleSheet* styleRules = new KwCssStyleSheet;

  KwCssStyleRule beachyTheme;
  beachyTheme.setCriteriaClasses(QSet<QString>() << "beachy");
  beachyTheme.setStyle<QBrush>("background.brush", Qt::black);
  beachyTheme.setStyle<QPixmap>("background.image.pixmap", QPixmap("/home/james/media/images/projector/misc/love-god-light.jpg"));
  styleRules->addRule(beachyTheme);

  m_primaryPlaylist->addStyleSheet(styleRules);
  m_primaryPlaylist->addItem(new KwPlaylistPresentation(QUrl("file:///home/james/Documents/test.odp")));

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

  // Small toolbar for group by action
  QToolBar* songTextToolBar = new QToolBar("Songs");
  songTextToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  songTextToolBar->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
  m_view->layoutSongsToolbar->layout()->addWidget(songTextToolBar);

  KActionMenu* groupByAction = new KActionMenu(KIcon("view-filter"), i18n("Group By"), songTextToolBar);
  groupByAction->setDelayed(false);
  songTextToolBar->addAction(groupByAction);

  // Rest of the toolbar
  QToolBar* songToolBar = new QToolBar("Songs");
  songToolBar->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
  m_view->layoutSongsToolbar->layout()->addWidget(songToolBar);

  KAction* addSongAction = new KAction(KIcon("list-add"), i18n("Add Song"), songToolBar);
  songToolBar->addAction(addSongAction);
  KAction* editSongAction = new KAction(KIcon("view-media-lyrics"), i18n("Edit Song"), songToolBar);
  songToolBar->addAction(editSongAction);
  KAction* addSongVersionAction = new KAction(KIcon("format-list-ordered"), i18n("Add Song Version"), songToolBar);
  songToolBar->addAction(addSongVersionAction);
  KAction* insertIntoPlaylistAction = new KAction(KIcon("player_playlist"), i18n("Insert Into Playlist"), songToolBar);
  songToolBar->addAction(insertIntoPlaylistAction);

  KMenu* groupByMenu = new KMenu(songToolBar);
  groupByAction->setMenu(groupByMenu);

  if (databaseOk)
  {
    KwSongdbTree* treeView = new KwSongdbTree(m_view);
    m_view->layoutSongsTree->addWidget(treeView);
    groupByMenu->addActions(treeView->groupByActions()->actions());
  }


  /*
   * Presentation
   */

  // Drop down list of presentations
  QComboBox* selectPresCombo = m_view->comboPresentations;
  m_selectPresTree = new QTreeView(this);
  m_selectPresTree->header()->hide();
  selectPresCombo->setModel(m_presentationManager->presentationsModel());
  selectPresCombo->setView(m_selectPresTree);
  m_selectPresTree->expandToDepth(0);
  m_selectPresTree->setItemsExpandable(false);
  connect(selectPresCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(presentationSelected(int)));

  // Presentations toolbar
  QToolBar* presToolBar = new QToolBar("Presentations");
  m_view->layoutPresentationsToolbar->layout()->addWidget(presToolBar);

  KActionMenu* openPresAction = new KActionMenu(KIcon("document-open"), "Open Presentation", presToolBar);
  openPresAction->setDelayed(true);
  presToolBar->addAction(openPresAction);

  KAction* refreshPresAction = new KAction(KIcon("view-refresh"), "Refresh Presentation List", presToolBar);
  presToolBar->addAction(refreshPresAction);

  KAction* closePresAction = new KAction(KIcon("fileclose"), "Close Presentation", presToolBar);
  presToolBar->addAction(closePresAction);

  KToggleAction* fullscreenPresAction = new KToggleAction(KIcon("view-fullscreen"), "Fullscreen Presentation Mode", presToolBar);
  presToolBar->addAction(fullscreenPresAction);

  // Slide list
  connect(m_view->listSlides, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slide_doubleClicked(QModelIndex)));

  // Slides toolbar
  QToolBar* slidesToolBar = new QToolBar("Slides");
  slidesToolBar->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
  slidesToolBar->setIconSize(QSize(32,32));
  m_view->layoutSlidesToolbar->layout()->addWidget(slidesToolBar);

  m_slideshowPrevSlideAction = new KAction(KIcon("media-skip-backward"), i18n("Previous Slide"), slidesToolBar);
  connect(m_slideshowPrevSlideAction, SIGNAL(triggered(bool)), this, SLOT(presentationPreviousSlide()));
  slidesToolBar->addAction(m_slideshowPrevSlideAction);

  m_slideshowPrevStepAction = new KAction(KIcon("media-seek-backward"), i18n("Previous Step"), slidesToolBar);
  connect(m_slideshowPrevStepAction, SIGNAL(triggered(bool)), this, SLOT(presentationPreviousStep()));
  slidesToolBar->addAction(m_slideshowPrevStepAction);

  m_slideshowNextStepAction = new KAction(KIcon("media-seek-forward"), i18n("Next Step"), slidesToolBar);
  connect(m_slideshowNextStepAction, SIGNAL(triggered(bool)), this, SLOT(presentationNextStep()));
  slidesToolBar->addAction(m_slideshowNextStepAction);

  m_slideshowNextSlideAction = new KAction(KIcon("media-skip-forward"), i18n("Next Slide"), slidesToolBar);
  connect(m_slideshowNextSlideAction, SIGNAL(triggered(bool)), this, SLOT(presentationNextSlide()));
  slidesToolBar->addAction(m_slideshowNextSlideAction);

  m_slideshowAction = new KToggleAction(KIcon("view-presentation"), i18n("Start/Stop Slideshow"), slidesToolBar);
  connect(m_slideshowAction, SIGNAL(toggled(bool)), this, SLOT(presentationToggled(bool)));
  slidesToolBar->addAction(m_slideshowAction);

  // Ensure the controls are as when slideshow is stopped
  m_slideshowAction->setEnabled(false);
  slideshowStopped();

  /*
   * Display startup
   */

  // Show the display on startup?
  if (Settings::displayShowStartup())
  {
    // If there's only one screen, don't bother showing display.
    QDesktopWidget* desktop = qobject_cast<QApplication*>(QCoreApplication::instance())->desktop();
    assert(0 != desktop);
    if (desktop->numScreens() > 1)
    {
      toggleMainDisplay(true);
      m_mainDisplayAction->setChecked(true);
    }
  }
}

kworship::~kworship()
{
  delete m_presentationManager;
  delete KwSongdb::self();
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
    m_mainDisplayAction = new KToggleAction(KIcon("video-projector"), i18n("Show Main Display"), this);
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
      m_mainDisplay->setWindowTitle("kworship display");
      m_displayController.attachChild(m_mainDisplay);
      connect(m_mainDisplay, SIGNAL(closed()), this, SLOT(mainDisplayClosed()));
    }

    QDesktopWidget* desktop = qobject_cast<QApplication*>(QCoreApplication::instance())->desktop();
    assert(0 != desktop);

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
  //avoid to have 2 dialogs shown
  if ( KConfigDialog::showDialog( "settings" ) )  {
    return;
  }
  KConfigDialog *dialog = new KConfigDialog(this, "settings", Settings::self());

  QWidget *generalSettingsDlg = new QWidget(dialog);
  ui_prefs_base.setupUi(generalSettingsDlg);
  dialog->addPage(generalSettingsDlg, i18n("General"), "preferences-other", i18n("General"));

  prefsDisplay *displaySettingsDlg = new prefsDisplay(dialog);
  dialog->addPage(displaySettingsDlg, i18n("Display"), "video-projector", i18n("Diaplay and Screen"));

  prefsSongDB *songdbSettingsDlg = new prefsSongDB(dialog);
  dialog->addPage(songdbSettingsDlg, i18n("Song DB"), "applications-multimedia", i18n("Song Database"));

  QWidget *presentationSettingsDlg = new QWidget(dialog);
  ui_prefsPresentations_base.setupUi(presentationSettingsDlg);
  dialog->addPage(presentationSettingsDlg, i18n("Presentations"), "view-presentation", i18n("Presentations and Slideshows"));

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

void kworship::presentationSelected(int)
{
  // Find the treeviews current index
  QModelIndex index = m_selectPresTree->currentIndex();
  UpPresentationsModel* model = m_presentationManager->presentationsModel();
  UpPresentationNode* presNode = dynamic_cast<UpPresentationNode*>(model->itemFromIndex(index));
  if (0 != presNode)
  {
    m_view->listSlides->setModel(model);
    m_view->listSlides->setRootIndex(index);
    setPresentation(presNode->getItem());
  }
  else
  {
    m_view->listSlides->setModel(0);
    setPresentation(0);
  }
}

void kworship::presentationToggled(bool checked)
{
  // Find the treeviews current index
  QModelIndex index = m_selectPresTree->currentIndex();
  UpPresentationsModel* model = m_presentationManager->presentationsModel();
  UpPresentationNode* presNode = dynamic_cast<UpPresentationNode*>(model->itemFromIndex(index));
  if (0 != presNode)
  {
    if (checked)
    {
      presNode->getItem()->startSlideshow();
    }
    else
    {
      presNode->getItem()->stopSlideshow();
    }
  }
}

void kworship::presentationPreviousSlide()
{
  // Find the treeviews current index
  QModelIndex index = m_selectPresTree->currentIndex();
  UpPresentationsModel* model = m_presentationManager->presentationsModel();
  UpPresentationNode* presNode = dynamic_cast<UpPresentationNode*>(model->itemFromIndex(index));
  if (0 != presNode)
  {
    presNode->getItem()->previousSlide();
  }
}

void kworship::presentationNextSlide()
{
  // Find the treeviews current index
  QModelIndex index = m_selectPresTree->currentIndex();
  UpPresentationsModel* model = m_presentationManager->presentationsModel();
  UpPresentationNode* presNode = dynamic_cast<UpPresentationNode*>(model->itemFromIndex(index));
  if (0 != presNode)
  {
    presNode->getItem()->nextSlide();
  }
}

void kworship::presentationPreviousStep()
{
  // Find the treeviews current index
  QModelIndex index = m_selectPresTree->currentIndex();
  UpPresentationsModel* model = m_presentationManager->presentationsModel();
  UpPresentationNode* presNode = dynamic_cast<UpPresentationNode*>(model->itemFromIndex(index));
  if (0 != presNode)
  {
    presNode->getItem()->previousStep();
  }
}

void kworship::presentationNextStep()
{
  // Find the treeviews current index
  QModelIndex index = m_selectPresTree->currentIndex();
  UpPresentationsModel* model = m_presentationManager->presentationsModel();
  UpPresentationNode* presNode = dynamic_cast<UpPresentationNode*>(model->itemFromIndex(index));
  if (0 != presNode)
  {
    presNode->getItem()->nextStep();
  }
}

void kworship::slide_doubleClicked(QModelIndex index)
{
  // Find the listviews current index
  UpPresentationsModel* model = m_presentationManager->presentationsModel();
  QModelIndex parentIndex = model->parent(index);
  UpPresentationNode* presNode = dynamic_cast<UpPresentationNode*>(model->itemFromIndex(parentIndex));
  if (0 != presNode)
  {
    presNode->getItem()->goToSlide(index.row());
  }
}

// Presentations
void kworship::setPresentation(UpPresentation* presentation)
{
  if (0 != m_currentPresentation)
  {
    // Stop the slideshow if its running
    m_currentPresentation->stopSlideshow();
    disconnect(m_currentPresentation, SIGNAL(slideshowStarted(int)), this, SLOT(slideshowStarted(int)));
    disconnect(m_currentPresentation, SIGNAL(slideshowStopped()), this, SLOT(slideshowStopped()));
    disconnect(m_currentPresentation, SIGNAL(slideshowSlideChanged(int, int)), this, SLOT(slideshowSlideChanged(int, int)));
    disconnect(m_currentPresentation, SIGNAL(slideshowStepChanged(int)), this, SLOT(slideshowStepChanged(int)));
  }
  m_currentPresentation = presentation;
  if (0 != m_currentPresentation)
  {
    connect(m_currentPresentation, SIGNAL(slideshowStarted(int)), this, SLOT(slideshowStarted(int)));
    connect(m_currentPresentation, SIGNAL(slideshowStopped()), this, SLOT(slideshowStopped()));
    connect(m_currentPresentation, SIGNAL(slideshowSlideChanged(int, int)), this, SLOT(slideshowSlideChanged(int, int)));
    connect(m_currentPresentation, SIGNAL(slideshowStepChanged(int)), this, SLOT(slideshowStepChanged(int)));
    if (m_currentPresentation->isSlideshowRunning())
    {
      slideshowStarted(m_currentPresentation->numSlidesInSlideshow());
      slideshowSlideChanged(m_currentPresentation->currentSlideshowSlide(), m_currentPresentation->stepsInCurrentSlideshowSlide());
      slideshowStepChanged(m_currentPresentation->currentSlideshowStep());
    }
  }
  m_slideshowAction->setEnabled(0 != m_currentPresentation);
}

// From current presentation
void kworship::slideshowStarted(int numSlides)
{
  m_view->progressPresSlides->setMaximum(numSlides);
  m_view->progressPresSlides->setVisible(true);
  m_slideshowAction->setChecked(true);
  m_slideshowPrevSlideAction->setEnabled(true);
  m_slideshowPrevStepAction->setEnabled(true);
  m_slideshowNextStepAction->setEnabled(true);
  m_slideshowNextSlideAction->setEnabled(true);
}

void kworship::slideshowStopped()
{
  m_view->progressPresSlides->setVisible(false);
  m_view->progressPresSteps->setVisible(false);
  m_slideshowAction->setChecked(false);
  m_slideshowPrevSlideAction->setEnabled(false);
  m_slideshowPrevStepAction->setEnabled(false);
  m_slideshowNextStepAction->setEnabled(false);
  m_slideshowNextSlideAction->setEnabled(false);
}

void kworship::slideshowSlideChanged(int slide, int numSteps)
{
  m_view->progressPresSlides->setValue(slide + 1);
  m_view->progressPresSteps->setMaximum(numSteps);
  m_view->progressPresSteps->setVisible(numSteps > 1);
}

void kworship::slideshowStepChanged(int step)
{
  m_view->progressPresSteps->setValue(step + 1);
}

#include "kworship.moc"
