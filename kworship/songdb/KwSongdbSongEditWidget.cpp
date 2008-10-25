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
  layoutSongBooksToolBar->layout()->addWidget(songBooksToolBar);
  {
    KAction* addAction = new KAction(KIcon("list-add"), i18n("Add Song Book Number"), songBooksToolBar);
    songBooksToolBar->addAction(addAction);

    KAction* removeAction = new KAction(KIcon("list-remove"), i18n("Remove Song Book Number"), songBooksToolBar);
    songBooksToolBar->addAction(removeAction);
  }

  // Lyrics markup toolbar
  QToolBar* lyricsMarkupToolBar = new QToolBar("lyricsMarkupToolBar");
  layoutLyricsMarkupToolBar->layout()->addWidget(lyricsMarkupToolBar);
  {
    KAction* addSongAction = new KAction(KIcon("list-add"), i18n("Add Verse"), lyricsMarkupToolBar);
    lyricsMarkupToolBar->addAction(addSongAction);
  }

  // Signals
  connect(listVersions, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
          this, SLOT(versionChanged(QListWidgetItem*, QListWidgetItem*)));
  connect(editLyricsMarkup, SIGNAL(textChanged()),
          this, SLOT(lyricsMarkupChanged()));

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

/// Save to database.
void KwSongdbSongEditWidget::save()
{
  /// @todo Implement me

  // Versions
  for (int i = 0; i < listVersions->count(); ++i)
  {
    KwSongdbVersionItem* item = dynamic_cast<KwSongdbVersionItem*>(listVersions->item(i));
    Q_ASSERT(0 != item);
    item->save();
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
    disconnect(this, SIGNAL(lyricsMarkupChangedSignal(const QString&)),
               previousVersion, SLOT(setLyricsMarkup(const QString&)));
  }

  if (0 != currentVersion)
  {
    editVersionName->setText(currentVersion->versionName());
    editVersionWriter->setText(currentVersion->writer());
    editVersionCopyright->setText(currentVersion->copyright());
    editLyricsMarkup->document()->setPlainText(currentVersion->lyricsMarkup());

    connect(editVersionName, SIGNAL(textEdited(const QString&)),
            currentVersion, SLOT(setVersionName(const QString&)));
    connect(editVersionWriter, SIGNAL(textEdited(const QString&)),
            currentVersion, SLOT(setWriter(const QString&)));
    connect(editVersionCopyright, SIGNAL(textEdited(const QString&)),
            currentVersion, SLOT(setCopyright(const QString&)));
    connect(this, SIGNAL(lyricsMarkupChangedSignal(const QString&)),
            currentVersion, SLOT(setLyricsMarkup(const QString&)));
  }
  frameVersion->setEnabled(0 != currentVersion);
  groupLyrics->setEnabled(0 != currentVersion);
}

/// Lyrics markup edit box has been modified.
void KwSongdbSongEditWidget::lyricsMarkupChanged()
{
  lyricsMarkupChangedSignal(editLyricsMarkup->document()->toPlainText());
}

