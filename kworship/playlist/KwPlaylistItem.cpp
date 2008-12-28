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
 * @file KwPlaylistItem.cpp
 * @brief An item that can be added to a playlist.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistItem.h"
#include "KwPlaylistUnknown.h"
#include "KwResourceLink.h"
#include <KwDisplayStyles.h>

#include <QDomDocument>
#include <QDomElement>

/*
 * Item factory
 */

/// Get a factory object.
KwPlaylistItem::Factory* KwPlaylistItem::factory()
{
  static Factory fac;
  return &fac;
}

/*
 * Constructors + destructor.
 */

/// Default constructor.
KwPlaylistItem::KwPlaylistItem()
: KwCssScope(KwDisplayStyles::schema())
, m_domDocument()
, m_domPreserve(m_domDocument.createDocumentFragment())
{
}

/// Construct from a DOM element.
KwPlaylistItem::KwPlaylistItem(const QDomElement& element, KwResourceManager* resourceManager)
: KwCssScope(KwDisplayStyles::schema())
, m_domDocument()
, m_domPreserve(m_domDocument.createDocumentFragment())
{
  // Import the children of element into m_domPreserve
  QDomNodeList children = element.childNodes();
  for (int i = 0; i < children.size(); ++i)
  {
    QDomNode child = children.item(i);
    if (child.isElement())
    {
      QDomElement childElement = child.toElement();
      if (childElement.tagName() == "resource")
      {
        QString name = childElement.attribute("name");
        if (!name.isEmpty())
        {
          setResource(name, new KwResourceLink(childElement, resourceManager));
          // Don't preserve this resource
          continue;
        }
      }
      else if (childElement.tagName() == "style")
      {
        importStylesFromDom(childElement, resourceManager);
        continue;
      }
    }
    QDomNode preserved = m_domDocument.importNode(child, true); // deep copy
    m_domPreserve.appendChild(preserved);
  }
}

/// Destructor.
KwPlaylistItem::~KwPlaylistItem()
{
  // Delete resource links
  Resources::iterator it;
  for (it = m_resources.begin(); it != m_resources.end(); ++it)
  {
    delete (*it).link;
  }
}

/*
 * DOM Translation.
 */

/// Create an item from a DOM element.
KwPlaylistItem* KwPlaylistItem::createFromDom(const QDomElement& element, KwResourceManager* resourceManager)
{
  // Look at the type
  QString type = element.attribute("type");
  KwPlaylistItem* item = factory()->construct(type, element, resourceManager);
  if (0 == item)
  {
    item = new KwPlaylistUnknown(element, resourceManager);
  }
  return item;
}

/// Export this item to the DOM.
void KwPlaylistItem::exportToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const
{
  // Add an item element with type attribute and child elements determined by type
  QDomElement itemElement = document.createElement("playlist_item");
  element.appendChild(itemElement);
  QString type = itemType();
  itemElement.setAttribute("type", type);

  if (!isScopeEmpty())
  {
    QDomElement styleElem = document.createElement("style");
    itemElement.appendChild(styleElem);
    exportStylesToDom(document, styleElem, resourceManager);
  }

  exportDetailsToDom(document, itemElement, resourceManager);

  // Export resources after type specific stuff so they can be modified at the last minute
  Resources::const_iterator it;
  for (it = m_resources.constBegin(); it != m_resources.constEnd(); ++it)
  {
    if (!(*it).link->isNull())
    {
      QDomElement resourceElement = document.createElement("resource");
      resourceElement.setAttribute("name", (*it).name);
      itemElement.appendChild(resourceElement);

      (*it).link->exportToDom(document, resourceElement, resourceManager);
    }
  }

  // Add preserve elements as well
  QDomNode importedFragment = document.importNode(m_domPreserve, true);
  itemElement.appendChild(importedFragment);
}

/*
 * Protected methods
 */

/// Indicate that elements of a particular tag name have been handled.
void KwPlaylistItem::elementsHandled(const QString& tagName)
{
  QDomElement current = m_domPreserve.firstChildElement(tagName);
  while (!current.isNull())
  {
    m_domPreserve.removeChild(current);
    current = current.nextSiblingElement(tagName);
  }
}

/// Indicate that the first elements of a particular tag name have been handled.
void KwPlaylistItem::elementHandled(const QString& tagName)
{
  QDomElement current = m_domPreserve.firstChildElement(tagName);
  if (!current.isNull())
  {
    m_domPreserve.removeChild(current);
  }
}

/// Get a resource by name.
KwResourceLink* KwPlaylistItem::getResource(const QString& name, bool create)
{
  Resources::iterator it;
  for (it = m_resources.begin(); it != m_resources.end(); ++it)
  {
    if ((*it).name == name)
    {
      return (*it).link;
    }
  }
  if (create)
  {
    Resource resource = { name, new KwResourceLink };
    m_resources.push_back(resource);
    return resource.link;
  }
  return 0;
}

/// Set a resource associated with a name.
KwResourceLink* KwPlaylistItem::setResource(const QString& name, KwResourceLink* link)
{
  deleteResource(name);
  Resource resource = { name, link };
  m_resources.push_back(resource);
  return link;
}

/// Delete a resource.
void KwPlaylistItem::deleteResource(const QString& name)
{
  Resources::iterator it;
  for (it = m_resources.begin(); it != m_resources.end(); ++it)
  {
    if ((*it).name == name)
    {
      delete (*it).link;
      m_resources.erase(it);
    }
  }
}

