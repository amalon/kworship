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

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwKWorshipFilter::KwKWorshipFilter()
: KwLoadSaveFilter()
{
  m_importMimeTypes += "application/x-kworship+xml";
  m_exportMimeTypes += "application/x-kworship+xml";
  m_importMimeTypes += "application/x-kworship-archive";
  m_exportMimeTypes += "application/x-kworship-archive";
}

/// Destructor.
KwKWorshipFilter::~KwKWorshipFilter()
{
}

/*
 * Main interface
 */

KwDocument* KwKWorshipFilter::load(const KUrl& url)
{
  // Start off by opening the archive file
  if (!url.isLocalFile())
  {
    KMessageBox::error(0,
        i18n("Non-local loads not yet supported"),
        i18n("KWorship"));
    return 0;
  }

  KwDocument* doc = new KwDocument(url);
  // Open archive object and fill it
  KwArchive* archive = new KwArchive(url.toLocalFile(), false);
  Q_ASSERT(archive->isReading());

  KwPlaylistList* playlist = archive->extractPlaylist("0");
  if (0 != playlist)
  {
    doc->setPlaylist(playlist);
  }

  delete archive;

  doc->setModified(false);

  return doc;
}

bool KwKWorshipFilter::save(KwDocument* doc, const KUrl& url)
{
  /// @todo Implement KwKWorshipFilter::save
  Q_ASSERT(false);
}

/*
 * Virtual interface
 */

void KwKWorshipFilter::v_saveLimitations(KwDocument* doc, Limitations* o_limitations)
{
  /// @todo Implement KwKWorshipFilter::v_saveLimitations
  Q_ASSERT(false);
}
