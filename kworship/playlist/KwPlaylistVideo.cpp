/**
 * @file KwPlaylistVideo.h
 * @brief An video playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistVideo.h"

#include "KwDisplayManager.h"

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

/// Destructor.
KwPlaylistVideo::~KwPlaylistVideo()
{
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

