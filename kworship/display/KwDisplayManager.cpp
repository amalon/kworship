/**
 * @file KwDisplayManager.cpp
 * @brief Display manager class.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwDisplayManager.h"

/*
 * Constructors + destructors
 */

/// Default constructor.
KwDisplayManager::KwDisplayManager(KwAbstractDisplay* display, KwMediaManager* mediaManager)
: background(mediaManager)
, text()
, overlay()
, m_mixer()
, m_mediaManager(mediaManager)
{
  m_mixer.attachChild(display);

  background.attachToMixer(&m_mixer);
  text.attachToMixer(&m_mixer);
  overlay.attachToMixer(&m_mixer);
}

/// Destructor.
KwDisplayManager::~KwDisplayManager()
{
}

/*
 * Main interface
 */

/// Apply the styles in a scope.
void KwDisplayManager::applyStyles(KwCssScope* scope)
{
  background.applyStyles(scope);
  text.applyStyles(scope);
  overlay.applyStyles(scope);
}

/*
 * Accessors
 */

/// Get the media manager.
KwMediaManager* KwDisplayManager::getMediaManager()
{
  return m_mediaManager;
}

