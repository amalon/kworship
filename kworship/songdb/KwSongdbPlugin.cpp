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

/**
 * @file KwSongdbPlugin.cpp
 * @brief Song database plugin.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbPlugin.h"
#include "KwSongdbTree.h"
#include "KwSongdb.h"
#include "KwSongdbSongEditDialog.h"
#include "KwSongdbSong.h"
#include "KwSongdbSongBooksEditWidget.h"
#include <KwApplication.h>
#include <kworship.h>

#include <KAction>
#include <KActionMenu>
#include <KActionCollection>
#include <KGenericFactory>
#include <KMenu>
#include <KMessageBox>

#include <QToolBar>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QSqlError>

K_EXPORT_COMPONENT_FACTORY( kworship_songdb, KGenericFactory<KwSongdbPlugin>("kworship_songdb") )

/*
 * Constructors + destructor
 */

/// Default constructor.
KwSongdbPlugin::KwSongdbPlugin(QObject* parent, const QStringList& params)
: KwPlugin(parent, "songdb",
           i18n("Songdb"),
           i18n("The song database plugin allows for the management and display of song lyrics."))
, m_songDbTree(0)
, m_unlockSongDbAction(0)
, m_lockSongDbAction(0)
, m_groupSongsByAction(0)
, m_addSongAction(0)
, m_editSongAction(0)
, m_editSongBooksAction(0)
{
  setXMLFile("songdb/kworship_songdbui.rc");

  // Set up actions

  m_unlockSongDbAction = new KAction(KIcon("document-decrypt"), i18n("Unlock Song Database"), this);
  actionCollection()->addAction( QLatin1String("unlock_song_database"), m_unlockSongDbAction);
  connect(m_unlockSongDbAction, SIGNAL(triggered(bool)), this, SLOT(songdbUnlock()));

  m_lockSongDbAction = new KAction(KIcon("document-encrypt"), i18n("Lock Song Database"), this);
  m_lockSongDbAction->setVisible(false);
  actionCollection()->addAction( QLatin1String("lock_song_database"), m_lockSongDbAction);
  connect(m_lockSongDbAction, SIGNAL(triggered(bool)), this, SLOT(songdbLock()));

  m_groupSongsByAction = new KActionMenu(KIcon("view-filter"), i18n("Group By"), this);
  m_groupSongsByAction->setDelayed(false);
  actionCollection()->addAction( QLatin1String("group_songs_by"), m_groupSongsByAction);

  m_addSongAction = new KAction(KIcon("list-add"), i18n("Add Song"), this);
  actionCollection()->addAction( QLatin1String("add_song"), m_addSongAction);
  connect(m_addSongAction, SIGNAL(triggered(bool)), this, SLOT(songdbAdd()));

  m_editSongAction = new KAction(KIcon("view-media-lyrics"), i18n("Edit Song"), this);
  actionCollection()->addAction( QLatin1String("edit_song"), m_editSongAction);
  connect(m_editSongAction, SIGNAL(triggered(bool)), this, SLOT(songdbEdit()));

  m_editSongBooksAction = new KAction(KIcon("format-list-ordered"), i18n("Edit Song Books"), this);
  actionCollection()->addAction( QLatin1String("edit_song_books"), m_editSongBooksAction);
  connect(m_editSongBooksAction, SIGNAL(triggered(bool)), this, SLOT(songdbEditSongBooks()));

  // Set up the docker
  m_docker = new QDockWidget(i18n("Song DB"));
  m_docker->setObjectName("dockSongdb");
  QWidget* mainDockWidget = new QWidget(/*m_docker*/);
  QVBoxLayout* dockLayout = new QVBoxLayout(mainDockWidget);
  m_docker->setWidget(mainDockWidget);

  // Ensure database is connected
  KwApplication* app = KwApplication::self();
  if (app->database().isOpen())
  {
    new KwSongdb(app->database());

    // Toolbar widget
    QWidget* toolbarWidget = new QWidget(mainDockWidget);
    dockLayout->addWidget(toolbarWidget);
    QHBoxLayout* toolbarLayout = new QHBoxLayout(toolbarWidget);

    // Small toolbar for group by action
    QToolBar* songTextToolBar = new QToolBar("Songs");
    songTextToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    songTextToolBar->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
    toolbarLayout->addWidget(songTextToolBar);

    songTextToolBar->addAction(m_groupSongsByAction);

    // Rest of the toolbar
    QToolBar* songToolBar = new QToolBar("Songs");
    songToolBar->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
    toolbarLayout->addWidget(songToolBar);

    songToolBar->addAction(m_addSongAction);
    songToolBar->addAction(m_editSongAction);
    songToolBar->addAction(m_editSongBooksAction);
    KAction* insertIntoPlaylistAction = new KAction(KIcon("player_playlist"), i18n("Insert Into Playlist"), songToolBar);
    songToolBar->addAction(insertIntoPlaylistAction);

    KMenu* groupByMenu = new KMenu(songToolBar);
    m_groupSongsByAction->setMenu(groupByMenu);

    m_songDbTree = new KwSongdbTree(mainDockWidget);
    dockLayout->addWidget(m_songDbTree);
    groupByMenu->addActions(m_songDbTree->groupByActions()->actions());
  }
  else
  {
    QLabel* labelNoDb = new QLabel(i18n("Song database not connected: %1", app->database().lastError().text()), mainDockWidget);
    dockLayout->addWidget(labelNoDb);
  }

  app->mainWindow()->addDockWidget(Qt::LeftDockWidgetArea, m_docker);
}

/// Destructor.
KwSongdbPlugin::~KwSongdbPlugin()
{
  delete KwSongdb::self();
}

/*
 * Slots
 */

void KwSongdbPlugin::songdbUnlock()
{
  m_unlockSongDbAction->setVisible(false);
  m_lockSongDbAction->setVisible(true);
}

void KwSongdbPlugin::songdbLock()
{
  m_unlockSongDbAction->setVisible(true);
  m_lockSongDbAction->setVisible(false);
}

void KwSongdbPlugin::songdbAdd()
{
  KwSongdbSongEditDialog* dialog = new KwSongdbSongEditDialog(0);
  dialog->setCaption(i18n("Add Song"));
  dialog->setAttribute(Qt::WA_DeleteOnClose, true);
  dialog->show();
}

void KwSongdbPlugin::songdbEdit()
{
  /// @todo Ensure the same song isn't open twice
  KwSongdbSong* song = m_songDbTree->currentSong();
  if (0 != song)
  {
    KwSongdbVersion* version = m_songDbTree->currentSongVersion();
    // version may be 0
    KwSongdbSongEditDialog* dialog = new KwSongdbSongEditDialog(song, version);
    dialog->setCaption(i18n("Edit Song - %1", song->name()));
    dialog->setAttribute(Qt::WA_DeleteOnClose, true);
    dialog->show();
  }
  else
  {
    KMessageBox::information(KwApplication::self()->mainWindow(), i18n("Please select a song."));
  }
}

void KwSongdbPlugin::songdbEditSongBooks()
{
  KwSongdbSongBooksEditWidget::showDialog();
}

/*
 * Loading and unloading virtual interface
 */

void KwSongdbPlugin::_load()
{
}

void KwSongdbPlugin::_unload()
{
}
