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
KwBackgroundManager::KwBackgroundManager(KwMediaManager* mediaManager)
: KwAbstractDisplayManager()
, m_mediaManager(mediaManager)
, m_imageLayer(0)
, m_videoLayer(0)
{
}

/// Destructor.
KwBackgroundManager::~KwBackgroundManager()
{
  clear();
}

/*
 * Main interface
 */

/// Clear the background.
void KwBackgroundManager::clear()
{
  m_display.clearLayers();
  delete m_imageLayer;
  delete m_videoLayer;
  m_imageLayer = 0;
  m_videoLayer = 0;
}

/// Set the background to an image.
void KwBackgroundManager::setImage(const QPixmap& pixmap)
{
  clear();
  m_imageLayer = new KwImageLayer(pixmap);
  m_display.setLayer(0, m_imageLayer, true);
}

/// Set the background up for video.
void KwBackgroundManager::setVideo()
{
  // Make sure the background video layer is set up
  if (0 == m_videoLayer)
  {
    clear();
    m_videoLayer = new KwVideoLayer(m_mediaManager);
    m_display.setLayer(0, m_videoLayer, true);
  }
}

