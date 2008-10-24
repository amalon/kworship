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
 * @file KwSongdbSongEditWidget.cpp
 * @brief Widget for editing a song.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbSongEditWidget.h"
#include "KwSongdbSong.h"
#include "KwSongdbVersion.h"
#include "KwSongdbVersionItem.h"

#include <KAction>

#include <QToolBar>

/*
 * Constructors + destructor
 */

/// Default constructor.
KwSongdbSongEditWidget::KwSongdbSongEditWidget()
: QWidget()
, Ui::KwSongdbSongEditWidget_base()
{
  setupUi(this);

  // Versions toolbar
  QToolBar* versionsToolBar = new QToolBar("versionsToolBar");
  layoutVersionsToolBar->layout()->addWidget(versionsToolBar);
  {
    KAction* addAction = new KAction(KIcon("list-add"), i18n("Add Song Version"), versionsToolBar);
    versionsToolBar->addAction(addAction);

    KAction* duplicateAction = new KAction(KIcon("duplicate"), i18n("Duplicate Song Version"), versionsToolBar);
    versionsToolBar->addAction(duplicateAction);
  }

  // Song books toolbar
  QToolBar* songBooksToolBar = new QToolBar("songBooksToolBar");
  songBooksToolBar->setOrientation(Qt::Vertical);
  layoutSongBooksToolBar->layout()->addWidget(songBooksToolBar);
  {
    KAction* addAction = new KAction(KIcon("list-add"), i18n("Add Song Book Number"), songBooksToolBar);
    songBooksToolBar->addAction(addAction);

    KAction* removeAction = new KAction(KIcon("list-remove"), i18n("Remove Song Book Number"), songBooksToolBar);
    songBooksToolBar->addAction(removeAction);
  }

  // Lyrics toolbar
  QToolBar* lyricsToolBar = new QToolBar("lyricsToolBar");
  lyricsToolBar->setOrientation(Qt::Vertical);
  layoutLyricsToolBar->layout()->addWidget(lyricsToolBar);
  {
    KAction* addSongAction = new KAction(KIcon("list-add"), i18n("Add Verse"), lyricsToolBar);
    lyricsToolBar->addAction(addSongAction);
  }

  // Arrangement toolbar
  QToolBar* arrangementToolBar = new QToolBar("arrangementToolBar");
  arrangementToolBar->setOrientation(Qt::Vertical);
  layoutArrangementToolBar->layout()->addWidget(arrangementToolBar);
  {
    KAction* useVerseAction = new KAction(KIcon("move-right"), i18n("Use Verse"), arrangementToolBar);
    arrangementToolBar->addAction(useVerseAction);

    KAction* moveUpAction = new KAction(KIcon("move-up"), i18n("Move Up"), arrangementToolBar);
    arrangementToolBar->addAction(moveUpAction);

    KAction* moveDownAction = new KAction(KIcon("move-down"), i18n("Move Down"), arrangementToolBar);
    arrangementToolBar->addAction(moveDownAction);
  }

  // Signals
  connect(listVersions, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
          this, SLOT(versionChanged(QListWidgetItem*, QListWidgetItem*)));

}

/// Destructor.
KwSongdbSongEditWidget::~KwSongdbSongEditWidget()
{
}

/*
 * Saving and loading
 */

/// Load from database.
void KwSongdbSongEditWidget::load(KwSongdbSong* song, KwSongdbVersion* selectedVersion)
{
  editSongName->setText(song->name());
  QList<KwSongdbVersion*> versions = song->versions();
  bool first = true;
  foreach (KwSongdbVersion* version, versions)
  {
    KwSongdbVersionItem* item = new KwSongdbVersionItem(version, listVersions);
    if ((0 == selectedVersion && first) || selectedVersion == version)
    {
      listVersions->setCurrentItem(item);
      first = false;
    }
  }
}

/*
 * Private slots
 */

/// A different version has been selected.
void KwSongdbSongEditWidget::versionChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
  KwSongdbVersionItem* previousVersion = dynamic_cast<KwSongdbVersionItem*>(previous);
  KwSongdbVersionItem* currentVersion = dynamic_cast<KwSongdbVersionItem*>(current);
  
  if (0 != previousVersion)
  {
    disconnect(editVersionName, SIGNAL(textEdited(const QString&)),
               previousVersion, SLOT(setVersionName(const QString&)));
    disconnect(editVersionWriter, SIGNAL(textEdited(const QString&)),
               previousVersion, SLOT(setWriter(const QString&)));
    disconnect(editVersionCopyright, SIGNAL(textEdited(const QString&)),
               previousVersion, SLOT(setCopyright(const QString&)));
  }

  if (0 != currentVersion)
  {
    editVersionName->setText(currentVersion->versionName());
    editVersionWriter->setText(currentVersion->writer());
    editVersionCopyright->setText(currentVersion->copyright());

    connect(editVersionName, SIGNAL(textEdited(const QString&)),
            currentVersion, SLOT(setVersionName(const QString&)));
    connect(editVersionWriter, SIGNAL(textEdited(const QString&)),
            currentVersion, SLOT(setWriter(const QString&)));
    connect(editVersionCopyright, SIGNAL(textEdited(const QString&)),
            currentVersion, SLOT(setCopyright(const QString&)));
  }
  frameVersion->setEnabled(0 != currentVersion);
  frameLyrics->setEnabled(0 != currentVersion);
}

