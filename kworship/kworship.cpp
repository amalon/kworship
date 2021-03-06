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

#include "kworship.h"
#include "kworshipview.h"
#include "settings.h"
#include "prefsDisplay.h"
#include "prefsDatabase.h"
#include "prefsPresentations.h"
#include "KwDatabaseSetup.h"
#include "KwDocument.h"
#include "KwApplication.h"
#include "KwPluginManager.h"
#include "KwFilterManager.h"
#include "KwLoadSaveFilter.h"

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

#include "UpManager.h"
#include "UpPresentationsModel.h"
#include "UpPresentation.h"
#include "UpPresentationNode.h"
#include "UpSlide.h"

#include <kconfigdialog.h>
#include <kstatusbar.h>
#include <kaction.h>
#include <kactionmenu.h>
#include <kmenu.h>
#include <ktoggleaction.h>
#include <kactioncollection.h>
#include <kstandardaction.h>
#include <KDE/KLocale>
#include <KFileDialog>
#include <KMessageBox>

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
#include <QTextEdit>

kworship::kworship()
: KXmlGuiWindow()
, m_view(new kworshipView(this))
, m_displayManager(0)
, m_document(0)
, m_presentationManager(new UpManager(this))
, m_currentPresentation(0)
, m_printer(0)
{
  m_playlistModel = new KwPlaylistModel;
  clearDocument();

  // set up presentation backends
  m_presentationManager->loadBackends();
  
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
  m_document->playlist()->addClass("beachy");

  KwCssStyleSheet* styleRules = new KwCssStyleSheet;

  KwCssStyleRule beachyTheme;
  beachyTheme.setCriteriaClasses(QSet<QString>() << "beachy");
  beachyTheme.setStyle<QBrush>("background.brush", Qt::black);
  beachyTheme.setStyle<KwResourceLink>("background.image.src", KUrl("file:///home/james/media/images/projector/misc/love-god-light.jpg"));
  styleRules->addRule(beachyTheme);

  KwCssStyleRule bibleTheme;
  bibleTheme.setCriteriaKeys(KwCssStyleRule::KeyList() << KwCssScopeKey(KwCssScopeKey::registerScopeType("bible")));
  bibleTheme.setStyle<QBrush>("background.brush", Qt::black);
  bibleTheme.setStyle<KwResourceLink>("background.image.src", KUrl("file:///home/james/media/images/projector/misc/bible.jpg"));
  styleRules->addRule(bibleTheme);

  m_document->playlist()->addStyleSheet(styleRules);

  m_view->treePlaylist->setModel(m_playlistModel);
  m_view->treePlaylist->setSelectionMode(QAbstractItemView::ExtendedSelection);
  m_view->treePlaylist->setExpandsOnDoubleClick(false);
  m_view->treePlaylist->setDragEnabled(true);
  m_view->treePlaylist->setAcceptDrops(true);

  connect(m_view->treePlaylist, SIGNAL(clicked(QModelIndex)), this, SLOT(playlist_clicked(QModelIndex)));
  connect(m_view->treePlaylist, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(playlist_doubleClicked(QModelIndex)));

  m_mediaManager = new KwMediaManager();
  m_mediaManager->linkAudio(new Phonon::AudioOutput(Phonon::MusicCategory));
  m_displayManager = new KwDisplayManager(&m_displayController, m_mediaManager);

  m_previewDisplay = new KwLocalDisplayPreview;
  m_view->layoutPreview->addWidget(m_previewDisplay);
  m_displayController.attachChild(m_previewDisplay);

  KwMediaControlWidget* mediaWidget = new KwMediaControlWidget(m_mediaManager, m_view->dockNowPlaying);
  m_view->layoutNowPlaying->addWidget(mediaWidget);

  /*
   * Presentation
   */

  // Drop down list of presentations
  QComboBox* selectPresCombo = m_view->comboPresentations;
  m_selectPresTree = new QTreeView(this);
  m_selectPresTree->header()->hide();
  selectPresCombo->setModel(m_presentationManager->presentationsModel());
  selectPresCombo->setView(m_selectPresTree);
  presentationComboReset();
  connect(m_presentationManager->presentationsModel(), SIGNAL(modelReset()), this, SLOT(presentationComboReset()));
  connect(selectPresCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(presentationSelected(int)));

  // Custom slideshow selector
  m_view->slideshows->setVisible(false);
  connect(m_view->comboSlideshows, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(changeSlideshowCombo(QString)));

  QToolBar* customSlideshowsToolBar = new QToolBar(i18n("Custom Slideshows"));
  customSlideshowsToolBar->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
  m_view->slideshows->layout()->addWidget(customSlideshowsToolBar);
  // Add slideshow to playlist
  KActionMenu* addSlideshowToPlaylistAction = new KActionMenu(KIcon("list-add"), i18n("Add Slideshow to Playlist"), customSlideshowsToolBar);
  addSlideshowToPlaylistAction->setDelayed(false);
  customSlideshowsToolBar->addAction(addSlideshowToPlaylistAction);
  {
    KAction* asLinkAction = new KAction(KIcon("insert-link"), i18n("Add Link to Slideshow into Playlist"), customSlideshowsToolBar);
    connect(asLinkAction, SIGNAL(triggered(bool)), this, SLOT(addSlideshowLinkToPlaylist()));
    addSlideshowToPlaylistAction->addAction(asLinkAction);
  }
  {
    KAction* asCopyAction = new KAction(KIcon("edit-copy"), i18n("Save Copy of Slideshow into Playlist"), customSlideshowsToolBar);
    connect(asCopyAction, SIGNAL(triggered(bool)), this, SLOT(addSlideshowCopyToPlaylist()));
    addSlideshowToPlaylistAction->addAction(asCopyAction);
  }

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

  // Slide notes
  m_slideNotes = new QTextEdit();
  m_slideNotes->setReadOnly(true);
  m_slideNotes->setWindowTitle(i18n("Slide Notes"));
  m_slideNotes->show();

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
  delete m_slideNotes;
}

/*
 * Public interface
 */

/// Load a specified playlist.
void kworship::loadPlaylist(const KUrl& url)
{
  // Find mime type
  KMimeType::Ptr mimeType = KMimeType::findByUrl(url);
  QString mime = mimeType->name();

  // Use the appropriate filter
  KwLoadSaveFilter* filter = KwApplication::self()->filterManager()->loadFilterFromMimeType(mime);
  if (filter)
  {
    KwDocument* newDoc = filter->load(url, mime);
    if (0 != newDoc)
    {
      delete m_document;
      m_document = newDoc;

      // Playlist will have changed
      playlistReset();

      // Wire up signals
      connect(m_document, SIGNAL(playlistReset()), this, SLOT(playlistReset()));
    }
    else
    {
      KMessageBox::error(this,
          i18n("Loading of \"%1\" failed.").arg(url.url()),
          i18n("KWorship"));
    }
  }
  else
  {
    KMessageBox::error(this,
        i18n("No load filter exists for the mime type \"%1\"").arg(mime),
        i18n("KWorship"));
  }
}

/*
 * Accessors
 */

/// Get the main display manager.
KwDisplayManager* kworship::displayManager()
{
  return m_displayManager;
}

/// Get the current document.
KwDocument* kworship::document()
{
  return m_document;
}

/// Get the playlist model.
KwPlaylistModel* kworship::playlistModel()
{
  return m_playlistModel;
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

  m_mainDisplayAction = new KToggleAction(KIcon("video-projector"), i18n("Show Main Display"), this);
  actionCollection()->addAction( QLatin1String("show_main_display"), m_mainDisplayAction );
  connect(m_mainDisplayAction, SIGNAL(triggered(bool)), this, SLOT(toggleMainDisplay(bool)));

  KAction* clearDisplayAction = new KAction(KIcon("clear"), i18n("Clear display"), this);
  actionCollection()->addAction( QLatin1String("display_clear"), clearDisplayAction);
  connect(clearDisplayAction, SIGNAL(triggered()), this, SLOT(displayClear()));

  // Playlist actions
  m_playlistInsertAction = new KAction(KIcon("insert"), i18n("Insert into playlist"), this);
  actionCollection()->addAction( QLatin1String("playlist_insert"), m_playlistInsertAction);
  connect(m_playlistInsertAction, SIGNAL(triggered()), this, SLOT(playlistInsert()));

  m_playlistDeleteAction = new KAction(KIcon("delete"), i18n("Delete from playlist"), this);
  m_playlistDeleteAction->setEnabled(false);
  actionCollection()->addAction( QLatin1String("playlist_delete"), m_playlistDeleteAction);
  connect(m_playlistDeleteAction, SIGNAL(triggered()), this, SLOT(playlistDelete()));

  m_playlistMoveUpAction = new KAction(KIcon("up"), i18n("Move playlist item up"), this);
  m_playlistMoveUpAction->setEnabled(false);
  actionCollection()->addAction( QLatin1String("playlist_move_up"), m_playlistMoveUpAction);
  connect(m_playlistMoveUpAction, SIGNAL(triggered()), this, SLOT(playlistMoveUp()));

  m_playlistMoveDownAction = new KAction(KIcon("down"), i18n("Move playlist item down"), this);
  m_playlistMoveDownAction->setEnabled(false);
  actionCollection()->addAction( QLatin1String("playlist_move_down"), m_playlistMoveDownAction);
  connect(m_playlistMoveDownAction, SIGNAL(triggered()), this, SLOT(playlistMoveDown()));
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

    if (!m_slideshowAction->isChecked())
    {
      m_mainDisplay->showFullScreen();
    }
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

bool kworship::askToSave()
{
  if (m_document->isModified())
  {
    switch (KMessageBox::questionYesNoCancel(this,
                                             i18n("The current playlist has been modified. "
                                                  "These modifications will be lost if you continue without saving. "
                                                  "Would you like to save now?"),
                                             i18n("Playlist is modified")))
    {
      case KMessageBox::Yes:
        {
          fileSave();
          // If the document is still modified, save must have been cancelled
          if (m_document->isModified())
          {
            return false;
          }
        }
        break;
      case KMessageBox::No:
        break;
      case KMessageBox::Cancel:
      default:
        {
          return false;
        }
        break;
    }
  }
  return true;
}

void kworship::fileNew()
{
  if (askToSave())
  {
    clearDocument();
  }
}

void kworship::fileOpen()
{
  if (askToSave())
  {
    // Do the open operation
    QStringList mimes = KwApplication::self()->filterManager()->loadMimeTypes();

    KUrl defaultUrl("kfiledialog:///playlist");
    if (m_document->isSaved())
    {
      defaultUrl = m_document->url();
    }

    KFileDialog dlg(defaultUrl, QString(), this);
    dlg.setMimeFilter(mimes);
    dlg.setOperationMode(KFileDialog::Opening);
    dlg.setCaption(i18n("Open Playlist"));
    dlg.setMode(KFile::File | KFile::ExistingOnly);
    dlg.exec();
    
    KUrl url = dlg.selectedUrl();
    if (!url.isEmpty())
    {
      loadPlaylist(url);
    }
  }
}

void kworship::fileSave()
{
  if (m_document->isSaved())
  {
    m_document->save();
  }
  else
  {
    fileSaveAs();
  }
}

void kworship::fileSaveAs()
{
  QStringList mimes = KwApplication::self()->filterManager()->saveMimeTypes();

  KUrl defaultUrl("kfiledialog:///playlist");
  if (m_document->isSaved())
  {
    defaultUrl = m_document->url();
  }

  QString defaultMime = m_document->mimeType();
  if (defaultMime.isEmpty())
  {
    defaultMime = KwApplication::self()->filterManager()->defaultSaveMimeType();
  }

  KFileDialog dlg(defaultUrl, QString(), this);
  dlg.setMimeFilter(mimes, defaultMime);
  dlg.setOperationMode(KFileDialog::Saving);
  dlg.setConfirmOverwrite(true);
  dlg.setCaption(i18n("Save Playlist As"));
  dlg.setMode(KFile::File);
  dlg.exec();
  
  KUrl url = dlg.selectedUrl();
  if (!url.isEmpty())
  {
    // Find mime type
    QString mime = dlg.currentMimeFilter();

    // Use the appropriate filter
    KwLoadSaveFilter* filter = KwApplication::self()->filterManager()->saveFilterFromMimeType(mime);
    if (filter)
    {
      m_document->saveAs(filter, mime, url);
      if (m_document->isModified())
      {
        KMessageBox::error(this,
            i18n("Saving to \"%1\" failed.").arg(url.url()),
            i18n("KWorship"));
      }
    }
    else
    {
      KMessageBox::error(this,
          i18n("No save filter exists for the mime type \"%1\"").arg(mime),
          i18n("KWorship"));
    }
  }
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
  dialog->addPage(displaySettingsDlg, i18n("Display"), "video-projector", i18n("Display and Screen"));

  prefsDatabase *songdbSettingsDlg = new prefsDatabase(dialog);
  dialog->addPage(songdbSettingsDlg, i18n("Database"), "applications-multimedia", i18n("Database"));

  prefsPresentations *presentationsSettingsDlg = new prefsPresentations(dialog);
  dialog->addPage(presentationsSettingsDlg, i18n("Presentations"), "view-presentation", i18n("Presentations and Slideshows"));

  // Let the plugins have their say
  KwApplication::self()->pluginManager()->setupConfigDialog(dialog);

  connect(dialog, SIGNAL(settingsChanged(QString)), m_view, SLOT(settingsChanged()));
  connect(dialog, SIGNAL(settingsChanged(QString)), this, SLOT(settingsChanged()));
  dialog->setAttribute( Qt::WA_DeleteOnClose );
  dialog->show();
}

void kworship::playlist_clicked(QModelIndex index)
{
  KwPlaylistNode* node = m_playlistModel->itemFromIndex(index);
  /// @todo Move this code to selection changed vfunc/slot of view so it can handle deselection
  // A node must be selected and correspond to a playlist item
  bool selected = (0 != node && 0 != node->playlistItem());
  m_playlistDeleteAction->setEnabled(selected);
  m_playlistMoveUpAction->setEnabled(selected);
  m_playlistMoveDownAction->setEnabled(selected);
}

void kworship::playlist_doubleClicked(QModelIndex index)
{
  KwPlaylistNode* node = m_playlistModel->itemFromIndex(index);
  node->activate(m_displayManager);
}

void kworship::playlistReset()
{
  // Connect up the new document
  m_playlistModel->setRootNode(m_document->playlist()->getNode(0));
}

void kworship::playlistInsert()
{
  KUrl defaultUrl("kfiledialog:///playlist_insert");

  KUrl::List urls = KFileDialog::getOpenUrls(defaultUrl, QString(), this, i18n("Insert Files into Playlist"));
  foreach (KUrl url, urls)
  {
    m_playlistModel->addFile(QModelIndex(), url);
  }
}

void kworship::playlistDelete()
{
  /// @todo Implement
}

void kworship::playlistMoveUp()
{
  /// @todo Implement
}

void kworship::playlistMoveDown()
{
  /// @todo Implement
}

#include <iostream>
/// Add the new docker to the interface.
void kworship::newDocker(QDockWidget* docker)
{
  std::cout << docker << std::endl;
  addDockWidget(Qt::LeftDockWidgetArea, docker);
}

void kworship::presentationDelete()
{
  setPresentation(0, true);
  presentationSelected(0);
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

// Documents
void kworship::clearDocument()
{
  delete m_document;
  m_document = new KwDocument(0, QString(), KUrl(), this);

  // Playlist will have changed
  playlistReset();

  // Wire up signals
  connect(m_document, SIGNAL(playlistReset()), this, SLOT(playlistReset()));
}

// Presentations
void kworship::setPresentation(UpPresentation* presentation, bool alreadyDestroyed)
{
  if (0 != m_currentPresentation)
  {
    // Stop the slideshow if its running
    m_view->slideshows->setVisible(false);
    if (!alreadyDestroyed)
    {
      m_currentPresentation->stopSlideshow();
      disconnect(m_currentPresentation, SIGNAL(currentSlideshowChanged(QString)), this, SLOT(changeSlideshowExternal(QString)));
      disconnect(m_currentPresentation, SIGNAL(customSlideshowsModified()), this, SLOT(refreshSlideshows()));
      disconnect(m_currentPresentation, SIGNAL(slideshowStarted(int)), this, SLOT(slideshowStarted(int)));
      disconnect(m_currentPresentation, SIGNAL(slideshowStopped()), this, SLOT(slideshowStopped()));
      disconnect(m_currentPresentation, SIGNAL(slideshowSlideChanged(int, int)), this, SLOT(slideshowSlideChanged(int, int)));
      disconnect(m_currentPresentation, SIGNAL(slideshowStepChanged(int)), this, SLOT(slideshowStepChanged(int)));
      disconnect(m_currentPresentation, SIGNAL(destroyed(QObject*)), this, SLOT(presentationDelete()));
    }
    slideshowStopped();
  }
  m_currentPresentation = presentation;
  if (0 != m_currentPresentation)
  {
    connect(m_currentPresentation, SIGNAL(currentSlideshowChanged(QString)), this, SLOT(changeSlideshowExternal(QString)));
    connect(m_currentPresentation, SIGNAL(customSlideshowsModified()), this, SLOT(refreshSlideshows()));
    connect(m_currentPresentation, SIGNAL(slideshowStarted(int)), this, SLOT(slideshowStarted(int)));
    connect(m_currentPresentation, SIGNAL(slideshowStopped()), this, SLOT(slideshowStopped()));
    connect(m_currentPresentation, SIGNAL(slideshowSlideChanged(int, int)), this, SLOT(slideshowSlideChanged(int, int)));
    connect(m_currentPresentation, SIGNAL(slideshowStepChanged(int)), this, SLOT(slideshowStepChanged(int)));
    connect(m_currentPresentation, SIGNAL(destroyed(QObject*)), this, SLOT(presentationDelete()));
    // update slideshows list
    refreshSlideshows();
    m_view->slideshows->setVisible(true);

    if (m_currentPresentation->isSlideshowRunning())
    {
      slideshowStarted(m_currentPresentation->numSlidesInSlideshow());
      slideshowSlideChanged(m_currentPresentation->currentSlideshowSlide(), m_currentPresentation->stepsInCurrentSlideshowSlide());
      slideshowStepChanged(m_currentPresentation->currentSlideshowStep());
    }
  }
  m_slideshowAction->setEnabled(0 != m_currentPresentation);
}

// Custom slideshows

void kworship::presentationComboReset()
{
  m_selectPresTree->expandToDepth(0);
  m_selectPresTree->setItemsExpandable(false);
}

void kworship::changeSlideshowCombo(QString name)
{
  Q_ASSERT(0 != m_currentPresentation);
  m_currentPresentation->setSlideshow(name);
  refreshSlides();
}

void kworship::changeSlideshowExternal(QString name)
{
  if (m_view->comboSlideshows->currentText() != name)
  {
    m_view->comboSlideshows->setCurrentIndex(m_view->comboSlideshows->findText(name));
    refreshSlides();
  }
}

void kworship::refreshSlideshows()
{
  Q_ASSERT(0 != m_currentPresentation);
  m_view->comboSlideshows->clear();
  m_view->comboSlideshows->insertItems(0, m_currentPresentation->slideshows());
  m_view->comboSlideshows->setCurrentIndex(m_view->comboSlideshows->findText(m_currentPresentation->currentSlideshow()));
}

void kworship::refreshSlides()
{
  // Clear child cache
  QModelIndex root = m_view->listSlides->rootIndex();
  DefaultModelNode* node = m_presentationManager->presentationsModel()->itemFromIndex(root);
  Q_ASSERT(0 != node);
  node->clearChildCache();

  // Force a refresh
  m_view->listSlides->setRootIndex(root);
}

void kworship::addSlideshowLinkToPlaylist()
{
  Q_ASSERT(0 != m_currentPresentation);
  QUrl url = m_currentPresentation->url();
  QString slideshow = m_currentPresentation->currentSlideshow();
  /// @todo Implement me
}
void kworship::addSlideshowCopyToPlaylist()
{
  Q_ASSERT(0 != m_currentPresentation);
  QString slideshow = m_currentPresentation->currentSlideshow();
  /// @todo Implement me
}

// From current presentation

void kworship::slideshowStarted(int numSlides)
{
  // Hide the screen
  if (0 != m_mainDisplay)
  {
    m_mainDisplay->hide();
  }

  // Clear the display
  m_displayManager->background.clear();
  m_displayManager->text.clear();

  m_view->slideshows->setEnabled(false);
  m_view->progressPresSlides->setMaximum(numSlides);
  m_view->progressPresSlides->setVisible(true);
  m_slideshowAction->setChecked(true);
}

void kworship::slideshowStopped()
{
  m_view->slideshows->setEnabled(true);
  m_view->progressPresSlides->setVisible(false);
  m_view->progressPresSteps->setVisible(false);
  m_slideshowAction->setChecked(false);
  m_slideshowPrevSlideAction->setEnabled(false);
  m_slideshowPrevStepAction->setEnabled(false);
  m_slideshowNextStepAction->setEnabled(false);
  m_slideshowNextSlideAction->setEnabled(false);

  // Clear any preview left from the slideshow
  m_displayManager->background.clear();
  // Clear slide notes
  m_slideNotes->document()->clear();

  // Show the screen again
  if (0 != m_mainDisplay)
  {
    m_mainDisplay->showFullScreen();
  }
}

void kworship::slideshowSlideChanged(int slide, int numSteps)
{
  m_view->progressPresSlides->setValue(slide + 1);
  m_view->progressPresSteps->setMaximum(numSteps);
  m_view->progressPresSteps->setVisible(numSteps > 1);

  m_slideshowPrevSlideAction->setEnabled(slide > 0);
  m_slideshowNextSlideAction->setEnabled(slide < m_view->progressPresSlides->maximum()-1);

  // live preview and notes
  m_slideNotes->document()->clear();
  assert(0 != m_currentPresentation);
  UpSlide* currentSlide = m_currentPresentation->slide(slide);
  if (0 != currentSlide)
  {
    // live preview
    if (Settings::presLivePreview())
    {
      m_displayManager->background.setImage(currentSlide->preview());
    }
    // notes
    currentSlide->writeNotes(m_slideNotes->document());
  }
}

void kworship::slideshowStepChanged(int step)
{
  m_view->progressPresSteps->setValue(step + 1);

  bool firstSlide = (m_view->progressPresSlides->value() <= 1);
  bool lastSlide = (m_view->progressPresSlides->value() >= m_view->progressPresSlides->maximum());
  bool firstStep = firstSlide && (step <= 0);
  bool lastStep = lastSlide && (step >= m_view->progressPresSteps->maximum() - 1);
  m_slideshowPrevStepAction->setEnabled(!firstStep);
  m_slideshowNextStepAction->setEnabled(!lastStep);
}


#include "kworship.moc"
