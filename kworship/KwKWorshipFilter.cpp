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
 * @file KwKWorshipFilter.cpp
 * @brief Main KWorship archive load and save filter.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwKWorshipFilter.h"
#include "KwDocument.h"
#include "KwArchive.h"
#include "KwPlaylistList.h"

#include <KUrl>
#include <KMessageBox>
#include <KLocale>
#include <KSaveFile>

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwKWorshipFilter::KwKWorshipFilter()
: KwLoadSaveFilter()
{
  m_importMimeTypes += "application/x-kworship-archive";
  m_exportMimeTypes += "application/x-kworship-archive";
  m_importMimeTypes += "application/x-kworship+xml";
  m_exportMimeTypes += "application/x-kworship+xml";
}

/// Destructor.
KwKWorshipFilter::~KwKWorshipFilter()
{
}

/*
 * Main interface
 */

KwDocument* KwKWorshipFilter::load(const KUrl& url, const QString& mimeType)
{
  /// @todo Handle non-local files
  if (!url.isLocalFile())
  {
    KMessageBox::error(0,
        i18n("Non-local loads not yet supported"),
        i18n("KWorship"));
    return 0;
  }

  KwDocument* doc = new KwDocument(this, mimeType, url);
  if (mimeType == "application/x-kworship-archive")
  {
    // Open archive object and read it
    KwArchive archive(url.toLocalFile(), false);
    Q_ASSERT(archive.isReading());

    KwPlaylistList* playlist = archive.extractPlaylist("0");
    if (0 != playlist)
    {
      doc->setPlaylist(playlist);
    }
  }
  else if (mimeType == "application/x-kworship+xml")
  {
    /// @todo Implement non-archived load
    Q_ASSERT(!"Non archived load not implemented");
  }
  else
  {
    Q_ASSERT(!"Unsupported mime type");
  }

  doc->setModified(false);

  return doc;
}

bool KwKWorshipFilter::save(KwDocument* doc, const KUrl& url, const QString& mimeType)
{
  /// @todo Handle non-local files
  if (!url.isLocalFile())
  {
    KMessageBox::error(0,
        i18n("Non-local loads not yet supported"),
        i18n("KWorship"));
    return false;
  }
  KSaveFile file;
  file.setFileName(url.toLocalFile());
  if (!file.open(QFile::WriteOnly))
  {
    KMessageBox::error(0,
        i18n("Cannot write file %1:\n%2.")
          .arg(file.fileName())
          .arg(file.errorString()),
        i18n("KWorship"));
    return false;
  }

  if (mimeType == "application/x-kworship-archive")
  {
    // Open archive object and fill it
    KwArchive archive(&file, true);
    Q_ASSERT(archive.isWriting());

    archive.addPlaylist(doc->playlist());
  }
  else if (mimeType == "application/x-kworship+xml")
  {
    /// @todo Implement non-archived save
    Q_ASSERT(!"Non archived save not implemented");
  }
  else
  {
    Q_ASSERT(!"Unsupported mime type");
  }

  if (!file.finalize())
  {
    KMessageBox::error(0,
        i18n("Cannot finalize file %1:\n%2.")
        .arg(file.fileName())
        .arg(file.errorString()),
        i18n("KWorship"));
    return false;
  }

  doc->setModified(false);

  return true;
}

/*
 * Virtual interface
 */

void KwKWorshipFilter::v_saveLimitations(KwDocument* doc, const QString& mimeType, Limitations* o_limitations)
{
  /// @todo Implement KwKWorshipFilter::v_saveLimitations
  Q_ASSERT(false);
}
