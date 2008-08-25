/**
 * @file KwBackgroundManager.cpp
 * @brief Background manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBackgroundManager.h"

#include "KwImageLayer.h"
#include "KwVideoLayer.h"

#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>

/*
 * Constructors + destructors
 */

/// Default constructor.
KwBackgroundManager::KwBackgroundManager()
{
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
  m_display.clearLayers();
  m_display.setLayer(0, background, true);
  /// @todo Delete previous layer
}

/// Set the background to a video.
void KwBackgroundManager::setVideo(QString path, bool loop, bool mute)
{
  Q_UNUSED(loop)

  Phonon::MediaObject* video = new Phonon::MediaObject();
  video->setCurrentSource(path);

  if (!mute)
  {
    Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory);
    Phonon::createPath(video, audioOutput);
  }

  KwVideoLayer* background = new KwVideoLayer(video);
  m_display.clearLayers();
  m_display.setLayer(0, background, true);
  /// @todo Delete previous layer

  video->play();
}

