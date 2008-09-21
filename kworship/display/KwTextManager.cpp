/***************************************************************************
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   This file is part of KWorship.                                        *
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
 * @file KwTextManager.cpp
 * @brief Text manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwTextManager.h"

#include "KwTextLayer.h"

/*
 * Constructors + destructors
 */

/// Default constructor.
KwTextManager::KwTextManager()
{
}

/// Destructor.
KwTextManager::~KwTextManager()
{
}

/*
 * Main interface
 */

/// Apply the styles in a scope.
void KwTextManager::applyStyles(KwCssScope* scope)
{
  Q_UNUSED(scope)
}

/// Clear all text.
void KwTextManager::clear()
{
  m_display.clearLayers();
}

/// Set the text.
void KwTextManager::setText(QString text)
{
  KwTextLayer* lyrics = new KwTextLayer(text);
  m_display.clearLayers();
  m_display.setLayer(0, lyrics, true);
  /// @todo Delete previous layer
}

