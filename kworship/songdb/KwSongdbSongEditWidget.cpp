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
#include "KwSongdbSongBook.h"
#include "KwSongdbSongBookSongItem.h"
#include "KwSongdbSongBooksEditWidget.h"
#include "KwSongdb.h"

#include <KAction>
#include <KDialog>

#include <QToolBar>

/*
 * Constructors + destructor
 */

/// Default constructor.
KwSongdbSongEditWidget::KwSongdbSongEditWidget()
: QWidget()
, Ui::KwSongdbSongEditWidget_base()
, m_song(0)
, m_currentVersion(0)
{
  setupUi(this);

  // Versions toolbar
  QToolBar* versionsToolBar = new QToolBar("versionsToolBar");
  layoutVersionsToolBar->layout()->addWidget(versionsToolBar);
  {
    KAction* addAction = new KAction(KIcon("list-add"), i18n("Add Song Version"), versionsToolBar);
    connect(addAction, SIGNAL(triggered(bool)),
            this, SLOT(addVersion()));
    versionsToolBar->addAction(addAction);

    KAction* duplicateAction = new KAction(KIcon("duplicate"), i18n("Duplicate Song Version"), versionsToolBar);
    versionsToolBar->addAction(duplicateAction);
  }

  // Song books toolbar
  QToolBar* songBooksToolBar = new QToolBar("songBooksToolBar");
  layoutSongBooksToolBar->layout()->addWidget(songBooksToolBar);
  {
    KAction* addAction = new KAction(KIcon("list-add"), i18n("Add Song Book Number"), songBooksToolBar);
    connect(addAction, SIGNAL(triggered(bool)),
            this, SLOT(addSongBookNumber()));
    songBooksToolBar->addAction(addAction);

    KAction* removeAction = new KAction(KIcon("list-remove"), i18n("Remove Song Book Number"), songBooksToolBar);
    connect(removeAction, SIGNAL(triggered(bool)),
            this, SLOT(removeSongBookNumber()));
    songBooksToolBar->addAction(removeAction);
  }

  // Lyrics markup toolbar
  QToolBar* lyricsMarkupToolBar = new QToolBar("lyricsMarkupToolBar");
  layoutLyricsMarkupToolBar->layout()->addWidget(lyricsMarkupToolBar);
  {
    KAction* addSongAction = new KAction(KIcon("list-add"), i18n("Add Verse"), lyricsMarkupToolBar);
    lyricsMarkupToolBar->addAction(addSongAction);
  }

  // Song books combobox
  updateSongBooks();

  // Signals
  connect(listVersions, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
          this, SLOT(versionChanged(QListWidgetItem*, QListWidgetItem*)));
  connect(listSongBooks, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
          this, SLOT(songBookNumberChanged(QListWidgetItem*, QListWidgetItem*)));
  connect(editLyricsMarkup, SIGNAL(textChanged()),
          this, SLOT(lyricsMarkupChanged()));
  connect(comboSongBooks, SIGNAL(currentIndexChanged(int)),
          this, SLOT(songBookChanged(int)));
  connect(btnEditSongBooks, SIGNAL(clicked()),
          this, SLOT(editSongBooksClicked()));

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
  m_song = song;
  editSongName->setText(song->name());
  QList<KwSongdbVersion*> versions = song->versions();
  bool first = true;
  foreach (KwSongdbVersion* version, versions)
  {
    KwSongdbVersionItem* item = new KwSongdbVersionItem(version, listVersions);
    if ((0 == selectedVersion && first) || selectedVersion == version)
    {
      listVersions->setCurrentItem(item);
    }
    first = false;
  }

  // If there are no versions, add one
  if (first)
  {
    addVersion();
  }
}

/// Save to database.
void KwSongdbSongEditWidget::save()
{
  // Song
  if (0 == m_song)
  {
    m_song = new KwSongdbSong();
  }
  m_song->setName(editSongName->text());
  m_song->save();

  // Versions
  for (int i = 0; i < listVersions->count(); ++i)
  {
    KwSongdbVersionItem* item = dynamic_cast<KwSongdbVersionItem*>(listVersions->item(i));
    Q_ASSERT(0 != item);
    item->save(m_song);
  }
}

/// Add a song version.
void KwSongdbSongEditWidget::addVersion()
{
  KwSongdbVersionItem* item = new KwSongdbVersionItem(listVersions);
  listVersions->setCurrentItem(item);
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

    // Remove song book numbers
    while (0 != listSongBooks->takeItem(0))
    {
      // remove the lot
    }
  }

  if (0 != currentVersion)
  {
    editVersionName->setText(currentVersion->versionName());
    editVersionWriter->setText(currentVersion->writer());
    editVersionCopyright->setText(currentVersion->copyright());
    editLyricsMarkup->document()->setPlainText(currentVersion->lyricsMarkup());

    // Insert song book numbers
    QList<KwSongdbSongBookSongItem*> songBookNumbers = currentVersion->songBookNumbers();
    foreach (KwSongdbSongBookSongItem* songBookNumber, songBookNumbers)
    {
      songBookNumber->updateText();
      listSongBooks->addItem(songBookNumber);
    }

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

  m_currentVersion = currentVersion;
}

/// A different song book number has been selected.
void KwSongdbSongEditWidget::songBookNumberChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
  KwSongdbSongBookSongItem* previousNumber = dynamic_cast<KwSongdbSongBookSongItem*>(previous);
  KwSongdbSongBookSongItem* currentNumber = dynamic_cast<KwSongdbSongBookSongItem*>(current);
  
  if (0 != previousNumber)
  {
    disconnect(this, SIGNAL(songBookChangedSignal(KwSongdbSongBook*)),
               previousNumber, SLOT(setSongBook(KwSongdbSongBook*)));
    disconnect(spinSongBookNumber, SIGNAL(valueChanged(int)),
               previousNumber, SLOT(setSongNumber(int)));

    comboSongBooks->setCurrentIndex(-1);
  }

  if (0 != currentNumber)
  {
    connect(this, SIGNAL(songBookChangedSignal(KwSongdbSongBook*)),
            currentNumber, SLOT(setSongBook(KwSongdbSongBook*)));
    connect(spinSongBookNumber, SIGNAL(valueChanged(int)),
            currentNumber, SLOT(setSongNumber(int)));

    KwSongdbSongBook* songBook = currentNumber->songBook();
    if (0 != songBook)
    {
      comboSongBooks->setCurrentIndex(comboSongBooks->findData(songBook->id()));
    }
    else
    {
      comboSongBooks->setCurrentIndex(-1);
    }
    spinSongBookNumber->setValue(currentNumber->songNumber());
  }
  groupSongBook->setEnabled(0 != currentNumber);
}

/// Lyrics markup edit box has been modified.
void KwSongdbSongEditWidget::lyricsMarkupChanged()
{
  lyricsMarkupChangedSignal(editLyricsMarkup->document()->toPlainText());
}

/// Selected song book has changed.
void KwSongdbSongEditWidget::songBookChanged(int index)
{
  if (index >= 0)
  {
    int id = comboSongBooks->itemData(index).toInt();
    KwSongdbSongBook* book = KwSongdb::self()->songBookById(id);
    if (0 != book)
    {
      songBookChangedSignal(book);
    }
  }
}

/// Button to edit song books has been clicked.
void KwSongdbSongEditWidget::editSongBooksClicked()
{
  KwSongdbSongBooksEditWidget* editor = KwSongdbSongBooksEditWidget::showDialog();
  connect(editor, SIGNAL(saved()),
          this, SLOT(updateSongBooks()));
}

/// Update the list of song books.
void KwSongdbSongEditWidget::updateSongBooks()
{
  KwSongdbVersionItem* version = m_currentVersion;
  versionChanged(0, version);

  comboSongBooks->clear();
  QList<KwSongdbSongBook*> songBooks = KwSongdb::self()->songBooks();
  foreach (KwSongdbSongBook* songBook, songBooks)
  {
    comboSongBooks->addItem(i18n("%1 - %2", songBook->abreviation(), songBook->name()), QVariant(songBook->id()));
  }

  versionChanged(version, 0);
}

/// Add a song book number to the version.
void KwSongdbSongEditWidget::addSongBookNumber()
{
  if (0 != m_currentVersion)
  {
    KwSongdbSongBookSongItem* item = m_currentVersion->addSongBookNumber();
    listSongBooks->addItem(item);
    listSongBooks->setCurrentItem(item);
  }
}

/// Remove the selected song book number.
void KwSongdbSongEditWidget::removeSongBookNumber()
{
}

