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
 * @file KwDataFile.cpp
 * @brief A KWorship XML data file.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwDataFile.h"
#include "KwResourceManager.h"
#include "KwPlaylistList.h"

#include <QDomDocument>

/*
 * Constructors + destructor
 */

/// Default constructor.
KwDataFile::KwDataFile()
: m_domDocument(new QDomDocument())
{
  QDomElement rootNode = m_domDocument->createElement("kworship");
  m_domDocument->appendChild(rootNode);
}

/// Destructor.
KwDataFile::~KwDataFile()
{
  delete m_domDocument;
}

/*
 * Playlists
 */

/// Insert a playlist.
void KwDataFile::insertPlaylist(const KwPlaylistList* playlist, KwResourceManager* resourceManager)
{
  QDomElement root = m_domDocument->documentElement();

  QDomElement playlistElement = m_domDocument->createElement("playlist");
  root.appendChild(playlistElement);

  playlist->exportToDom(*m_domDocument, playlistElement, resourceManager);
}

/// Create a playlist object from the data.
KwPlaylistList* KwDataFile::createPlaylist(KwResourceManager* resourceManager) const
{
  QDomElement root = m_domDocument->documentElement();

  QDomElement playlistElement = root.firstChildElement("playlist");
  if (!playlistElement.isNull())
  {
    QDomElement playlistItemElement = playlistElement.firstChildElement("playlist_item");
    if (playlistItemElement.attribute("type") == "list")
    {
      return new KwPlaylistList(playlistItemElement, resourceManager);
    }
  }

  return 0;
}

/*
 * Reading and writing
 */

/// Read from device.
void KwDataFile::readFrom(QIODevice* device)
{
  m_domDocument->setContent(device);
}

/// Write to stream.
void KwDataFile::writeTo(QTextStream& stream) const
{
  m_domDocument->save(stream, 0);
}

