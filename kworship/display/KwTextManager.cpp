/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   KWorship is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   KWorship is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with KWorship.  If not, write to the Free Software Foundation,  *
 *   Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.   *
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
: m_style()
, m_currentLayer(0)
{
}

/// Destructor.
KwTextManager::~KwTextManager()
{
  delete m_currentLayer;
}

/*
 * Main interface
 */

/// Apply the styles in a scope.
void KwTextManager::applyStyles(KwCssScope* scope)
{
  m_style.loadFrom(scope);
}

/// Clear all text.
void KwTextManager::clear()
{
  m_display.clearLayers();
}

/// Set the text.
void KwTextManager::setText(const QString& text)
{
  KwTextLayer* lyrics = new KwTextLayer(text);
  lyrics->setStyle(m_style);
  m_display.clearLayers();
  m_display.setLayer(0, lyrics, true);

  delete m_currentLayer;
  m_currentLayer = lyrics;
}

/// Set formatted text.
void KwTextManager::setHtml(const QString& html)
{
  KwTextLayer* lyrics = new KwTextLayer(html, true);
  lyrics->setStyle(m_style);
  m_display.clearLayers();
  m_display.setLayer(0, lyrics, true);

  delete m_currentLayer;
  m_currentLayer = lyrics;
}

