/**
 * @file KwAbstractDisplayManager.cpp
 * @brief Abstract display manager class.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractDisplayManager.h"
#include "KwDisplayMixer.h"

/*
 * Constructors + destructors
 */

/// Default constructor.
KwAbstractDisplayManager::KwAbstractDisplayManager()
: m_display()
{
}

/// Destructor.
KwAbstractDisplayManager::~KwAbstractDisplayManager()
{
}

/*
 * Main interface
 */

/// Attach the display to the top of a mixer.
void KwAbstractDisplayManager::attachToMixer(KwDisplayMixer* mixer)
{
  mixer->attachDisplayToTop(&m_display);
}

