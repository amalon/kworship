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
  // Reserve a layer.
  m_display.setLayer(0, 0, true);
}

/// Destructor.
KwTextManager::~KwTextManager()
{
}

/*
 * Main interface
 */

/// Set the text.
void KwTextManager::setText(QString text)
{
  KwTextLayer* lyrics = new KwTextLayer(text);
  m_display.setLayer(0, lyrics);
  /// @todo Delete previous layer
}

