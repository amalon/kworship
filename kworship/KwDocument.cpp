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
#include "KwPlaylistList.h"
#include "KwLoadSaveFilter.h"

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwDocument::KwDocument(KwLoadSaveFilter* filter, const QString& mimeType, KUrl url, QObject* parent)
: QObject(parent)
, m_url(url)
, m_mimeType(mimeType)
, m_activeFilter(filter)
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

/// Get the current mime type.
const QString& KwDocument::mimeType() const
{
  return m_mimeType;
}

/*
 * Mutators
 */

/// Set the main playlist.
void KwDocument::setPlaylist(KwPlaylistList* playlist)
{
  delete m_playlist;
  m_playlist = playlist;
  emit playlistReset();
}

/*
 * Saving and loading actions
 */

/// Save the file.
void KwDocument::save()
{
  Q_ASSERT(0 != m_activeFilter);
  bool success = m_activeFilter->save(this, m_url, m_mimeType);
  if (success)
  {
    setModified(false);
  }
}

/// Save the file to a different URL.
void KwDocument::saveAs(KwLoadSaveFilter* filter, const QString& mimeType, const KUrl& url)
{
  bool success = filter->save(this, url, mimeType);
  if (success)
  {
    m_activeFilter = filter;
    m_mimeType = mimeType;
    m_url = url;
  }
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
