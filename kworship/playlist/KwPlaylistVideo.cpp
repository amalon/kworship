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
KwPlaylistVideo::KwPlaylistVideo(QString url)
: KwPlaylistFile(url)
{
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
  manager->text.clear();
  manager->background.setVideo(getUrl(), false, false);
}

