/**
 * @file KwBackgroundManager.cpp
 * @brief Background manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBackgroundManager.h"

#include "KwImageLayer.h"

/*
 * Constructors + destructors
 */

/// Default constructor.
KwBackgroundManager::KwBackgroundManager()
{
  // Reserve a layer.
  m_display.setLayer(0, 0, true);
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
  m_display.setLayer(0, background);
  /// @todo Delete previous layer
}
