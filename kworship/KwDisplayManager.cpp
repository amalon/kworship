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
KwDisplayManager::KwDisplayManager(KwAbstractDisplay* display)
: m_mixer()
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

