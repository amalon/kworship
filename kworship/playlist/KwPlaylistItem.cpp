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

#include <QDomDocument>
#include <QDomElement>

/*
 * Constructors + destructor.
 */

/// Default constructor.
KwPlaylistItem::KwPlaylistItem()
: KwCssScope()
{
}

/// Destructor.
KwPlaylistItem::~KwPlaylistItem()
{
}

/*
 * DOM Translation.
 */

/// Export this item to the DOM.
void KwPlaylistItem::exportToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const
{
  // Add an item element with type attribute and child elements determined by type
  QDomElement itemElement = document.createElement("playlist_item");
  element.appendChild(itemElement);
  QString type = itemType();
  itemElement.setAttribute("type", type);

  exportDetailsToDom(document, itemElement, resourceManager);
}

