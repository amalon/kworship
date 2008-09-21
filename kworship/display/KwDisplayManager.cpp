/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   KWorship is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   KWorship is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with KWorship.  If not, see <http://www.gnu.org/licenses/>.     *
 ***************************************************************************/

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

