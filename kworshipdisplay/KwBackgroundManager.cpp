/**
 * @file KwBackgroundManager.cpp
 * @brief Background manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBackgroundManager.h"

#include "KwImageLayer.h"
#include "KwVideoLayer.h"

#include <phonon/mediaobject.h>

/*
 * Constructors + destructors
 */

/// Default constructor.
KwBackgroundManager::KwBackgroundManager()
{
  // Reserve a layer.
  m_display.setLayer(0, 0, true);
}

/// Destructor.
KwBackgroundManager::~KwBackgroundManager()
{
}

/*
 * Main interface
 */

/// Set the background to an image.
void KwBackgroundManager::setImage(const QPixmap& pixmap)
{
  KwImageLayer* background = new KwImageLayer(pixmap);
  m_display.setLayer(0, background);
  /// @todo Delete previous layer
}

/// Set the background to a video.
void KwBackgroundManager::setVideo(QString path)
{
  Phonon::MediaObject* video = new Phonon::MediaObject();
  video->setCurrentSource(path);

  KwVideoLayer* background = new KwVideoLayer(video);
  m_display.setLayer(0, background);
  /// @todo Delete previous layer

  video->play();
}

