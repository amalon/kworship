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
 * @file KwDocument.cpp
 * @brief A KWorship document (anything saved in a KWorship data file).
 * @author James Hogan <james@albanarts.com>
 */

#include "KwDocument.h"
#include "KwArchive.h"
#include "KwPlaylistList.h"

#include <KSaveFile>
#include <KLocale>
#include <KMessageBox>

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwDocument::KwDocument(KUrl url, QObject* parent)
: QObject(parent)
, m_url(url)
, m_modified(false)
, m_playlist(new KwPlaylistList())
{
}

/// Destructor.
KwDocument::~KwDocument()
{
  delete m_playlist;
}

/*
 * Accessors
 */

/// Find whether the document has been modified.
bool KwDocument::isModified() const
{
  return m_modified;
}

/// Find whether the document has ever been saved.
bool KwDocument::isSaved() const
{
  return !m_url.isEmpty();
}

/// Get the URL the document is saved at.
KUrl KwDocument::url() const
{
  return m_url;
}

/// Get the main playlist.
KwPlaylistList* KwDocument::playlist()
{
  return m_playlist;
}

/*
 * Saving and loading actions
 */

/// Load the file.
void KwDocument::reload()
{
  // Start off by opening the archive file
  if (!m_url.isLocalFile())
  {
    KMessageBox::error(0,
        i18n("Non-local loads not yet supported"),
        i18n("KWorship"));
    return;
  }

  // Create a new archive object and fill it
  KwArchive* archive = new KwArchive(m_url.toLocalFile(), false);
  loadFromArchive(archive);
  delete archive;

  setModified(false);
}

/// Save the file.
void KwDocument::save()
{
  Q_ASSERT(isSaved());

  // Start off by opening the archive file
  if (!m_url.isLocalFile())
  {
    KMessageBox::error(0,
        i18n("Non-local saves not yet supported"),
        i18n("KWorship"));
    return;
  }
  KSaveFile file;
  file.setFileName(m_url.toLocalFile());
  if (!file.open(QFile::WriteOnly))
  {
    KMessageBox::error(0,
        i18n("Cannot write file %1:\n%2.")
          .arg(file.fileName())
          .arg(file.errorString()),
        i18n("KWorship"));
    return;
  }

  // Create a new archive object and fill it
  KwArchive* archive = new KwArchive(&file, true);
  saveToArchive(archive);
  delete archive;

  if (!file.finalize())
  {
    KMessageBox::error(0,
        i18n("Cannot finalize file %1:\n%2.")
          .arg(file.fileName())
          .arg(file.errorString()),
        i18n("KWorship"));
    return;
  }

  setModified(false);
}

/// Save the file to a different URL.
void KwDocument::saveAs(const KUrl& url)
{
  m_url = url;
  save();
}

/*
 * Other slots
 */

/// Set whether the file is modified.
void KwDocument::setModified(bool modified)
{
  if (m_modified != modified)
  {
    m_modified = modified;
    modifiedChanged(modified);
  }
}

/*
 * Archive interface.
 */

/// Load from an archive.
void KwDocument::loadFromArchive(KwArchive* archive)
{
  Q_ASSERT(archive->isReading());

  KwPlaylistList* playlist = archive->extractPlaylist("0");
  if (0 != playlist)
  {
    delete m_playlist;
    m_playlist = playlist;
    playlistReset();
  }
}

/// Save to an archive.
void KwDocument::saveToArchive(KwArchive* archive) const
{
  Q_ASSERT(archive->isWriting());

  archive->addPlaylist(m_playlist);
}

