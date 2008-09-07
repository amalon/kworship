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

