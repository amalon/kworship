/**
 * @file KwPlaylistImage.h
 * @brief An image playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistImage.h"

#include "KwDisplayManager.h"

#include <cassert>

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
 * Main interface.
 */

void KwPlaylistImage::activate(KwDisplayManager* manager)
{
  manager->text.clear();
  manager->background.setImage(QPixmap(getUrl().path()));
}

