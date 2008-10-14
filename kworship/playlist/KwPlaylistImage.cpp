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
 * @file KwPlaylistImage.h
 * @brief An image playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistImage.h"

#include "KwDisplayManager.h"

/*
 * Constructors + destructor.
 */

/// Default constructor.
KwPlaylistImage::KwPlaylistImage(const QUrl& url)
: KwPlaylistFile(url)
{
}

/// Destructor.
KwPlaylistImage::~KwPlaylistImage()
{
}

/*
 * DOM Translation.
 */

QString KwPlaylistImage::itemType() const
{
  return "image";
}

void KwPlaylistImage::exportDetailsToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const
{
}

/*
 * Main interface.
 */

void KwPlaylistImage::activate(KwDisplayManager* manager)
{
  manager->text.clear();
  manager->background.setImage(QPixmap(getUrl().path()));
}

