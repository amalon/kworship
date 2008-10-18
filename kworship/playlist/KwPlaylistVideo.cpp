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
 * @file KwPlaylistVideo.h
 * @brief An video playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistVideo.h"
#include "KwDisplayManager.h"

KW_REGISTER_PLAYLIST_ITEM(KwPlaylistVideo, "video")

/*
 * Constructors + destructor.
 */

/// Default constructor.
KwPlaylistVideo::KwPlaylistVideo(const QUrl& url)
: KwPlaylistFile(url)
, m_mediaItem(url)
{
  m_mediaItem.setAudio(true);
  m_mediaItem.setVideo(true);
}

/// Construct from a DOM element.
KwPlaylistVideo::KwPlaylistVideo(const QDomElement& element, KwResourceManager* resourceManager)
: KwPlaylistFile(element, resourceManager)
, m_mediaItem(getUrl())
{
  m_mediaItem.setAudio(true);
  m_mediaItem.setVideo(true);
}

/// Destructor.
KwPlaylistVideo::~KwPlaylistVideo()
{
}

/*
 * DOM Translation.
 */

QString KwPlaylistVideo::itemType() const
{
  return "video";
}

void KwPlaylistVideo::exportDetailsToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const
{
  KwPlaylistFile::exportDetailsToDom(document, element, resourceManager);
}

/*
 * Main interface.
 */

void KwPlaylistVideo::activate(KwDisplayManager* manager)
{
  manager->background.setVideo();
  manager->text.clear();
  m_mediaItem.playMedia(manager->getMediaManager());
}

