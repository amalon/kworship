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
 * @file KwPlaylistList.cpp
 * @brief A list of playlist items.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistList.h"
#include "KwPlaylistListNode.h"

#include <QDomElement>

#include <cassert>

KW_REGISTER_PLAYLIST_ITEM(KwPlaylistList, "list")

/*
 * Constructors + destructor.
 */

/// Default constructor.
KwPlaylistList::KwPlaylistList()
: KwPlaylistItem()
, m_playlist()
{
}

/// Construct from a DOM element.
KwPlaylistList::KwPlaylistList(const QDomElement& element, KwResourceManager* resourceManager)
: KwPlaylistItem(element, resourceManager)
{
  elementsHandled("playlist_items");
  QDomElement list = element.firstChildElement("playlist_items");
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
          addItem(item);
        }
      }
    }
    list = list.nextSiblingElement("playlist_items");
  }
}

/// Destructor.
KwPlaylistList::~KwPlaylistList()
{
}

/*
 * Child management.
 */

/// Add a child.
void KwPlaylistList::addItem(KwPlaylistItem* item, int position)
{
  if (position == -1)
  {
    m_playlist.push_back(item);
  }
  else
  {
    m_playlist.insert(position, item);
  }
  item->setParentScope(this);
}

/// Get the number of children.
int KwPlaylistList::getItemCount() const
{
  return m_playlist.size();
}

/// Get a specific child.
KwPlaylistItem* KwPlaylistList::getItem(int index)
{
  assert(index < getItemCount());
  Playlist::iterator it = m_playlist.begin();
  while (index && it != m_playlist.end())
  {
    ++it;
    --index;
  }
  assert(it != m_playlist.end());
  if (it == m_playlist.end())
  {
    return 0;
  }
  else
  {
    return *it;
  }
}
/// Get a specific child.
const KwPlaylistItem* KwPlaylistList::getItem(int index) const
{
  assert(index < getItemCount());
  Playlist::const_iterator it = m_playlist.constBegin();
  while (index && it != m_playlist.constEnd())
  {
    ++it;
    --index;
  }
  assert(it != m_playlist.constEnd());
  if (it == m_playlist.constEnd())
  {
    return 0;
  }
  else
  {
    return *it;
  }
}

/*
 * DOM Translation.
 */

QString KwPlaylistList::itemType() const
{
  return "list";
}

void KwPlaylistList::exportDetailsToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const
{
  QDomElement children = document.createElement("playlist_items");
  element.appendChild(children);

  foreach (const KwPlaylistItem* item, m_playlist)
  {
    item->exportToDom(document, children, resourceManager);
  }
}

/*
 * Main interface.
 */

KwPlaylistNode* KwPlaylistList::getNode(KwPlaylistNode* parent)
{
  return new KwPlaylistListNode(parent, this);
}

