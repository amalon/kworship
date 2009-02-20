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
 * @file KwPlaylistFile.h
 * @brief An image playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistFile.h"
#include "KwPlaylistFileNode.h"
#include "KwResourceLink.h"

#include <QDomDocument>
#include <QDomElement>

KW_REGISTER_PLAYLIST_ITEM(KwPlaylistFile, "file")

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistFile::KwPlaylistFile(const QUrl& url)
: KwPlaylistItem()
, m_title(url.toLocalFile())
, m_resource(setResource("file", new KwResourceLink(url)))
{
}

/// Construct from a DOM element.
KwPlaylistFile::KwPlaylistFile(const QDomElement& element, KwResourceManager* resourceManager)
: KwPlaylistItem(element, resourceManager)
, m_title()
, m_resource(getResource("file"))
{
  m_title = m_resource->url().pathOrUrl();
}

/// Destructor.
KwPlaylistFile::~KwPlaylistFile()
{
}

/*
 * DOM Translation.
 */

QString KwPlaylistFile::itemType() const
{
  return "file";
}

void KwPlaylistFile::exportDetailsToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const
{
}

/*
 * Main interface.
 */

KwPlaylistNode* KwPlaylistFile::getNode(KwPlaylistNode* parent)
{
  return new KwPlaylistFileNode(parent, this);
}

/// Activate the file.
void KwPlaylistFile::activate(KwDisplayManager*)
{
}

/*
 * Accessors
 */

/// Get the image url.
QUrl KwPlaylistFile::getUrl() const
{
  return m_resource->url();
}

/// Get the title.
const QString& KwPlaylistFile::title() const
{
  return m_title;
}

/*
 * Mutators
 */

/// Set the title to display.
void KwPlaylistFile::setTitle(const QString& title)
{
  m_title = title;
}
