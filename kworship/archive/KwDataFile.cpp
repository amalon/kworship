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
 * Individual playlist items
 */

/** Insert a set of playlist items.
 * @param items List of playlist items to insert.
 * @param resources Resource manager.
 */
void KwDataFile::insertPlaylistItems(const QList<KwPlaylistItem*>& items, KwResourceManager* resourceManager)
{
  QDomElement root = m_domDocument->documentElement();

  QDomElement children = m_domDocument->createElement("playlist_items");
  root.appendChild(children);

  foreach (const KwPlaylistItem* item, items)
  {
    item->exportToDom(*m_domDocument, children, resourceManager);
  }
}

/** Create a set of playlist items from the data.
 * @param resources Resource manager.
 * @returns Newly created playlist items which the user must delete.
 */
QList<KwPlaylistItem*> KwDataFile::extractPlaylistItems(KwResourceManager* resourceManager) const
{
  QDomElement root = m_domDocument->documentElement();
  QList<KwPlaylistItem*> items;

  QDomElement list = root.firstChildElement("playlist_items");
  while (!list.isNull())
  {
    QDomNodeList children = list.childNodes();
    for (int i = 0; i < children.count(); ++i)
    {
      QDomElement child = children.item(i).toElement();
      if (!child.isNull())
      {
        KwPlaylistItem* item = KwPlaylistItem::createFromDom(child, resourceManager);
        if (0 != item)
        {
          items << item;
        }
      }
    }
    list = list.nextSiblingElement("playlist_items");
  }

  return items;
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
KwPlaylistList* KwDataFile::extractPlaylist(KwResourceManager* resourceManager) const
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
 * Main resource interface
 */

#include <QtDebug>
void KwDataFile::addResource(const KwResourceLink* link)
{
  // Basically don't do anything, but perhaps report it
  qDebug() << __PRETTY_FUNCTION__ << "(" << link << ") - Ignoring";
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

