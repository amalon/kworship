/**
 * @file KwMediaPreferencesVisual.cpp
 * @brief A media item's visual preferences.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwMediaPreferencesVisual.h"

/*
 * Constructors + destructors
 */

/// Default constructor.
KwMediaPreferencesVisual::KwMediaPreferencesVisual()
: m_brightness(0.0)
, m_contrast(0.0)
, m_hue(0.0)
, m_saturation(0.0)
, m_scaleMode(Stretch)
{
}

/// Destructor.
KwMediaPreferencesVisual::~KwMediaPreferencesVisual()
{
}

/*
 * Accessors
 */

/// Get the brightness value.
KwMediaPreferencesVisual::Parameter KwMediaPreferencesVisual::getBrightness() const
{
  return m_brightness;
}

/// Get the contrast value.
KwMediaPreferencesVisual::Parameter KwMediaPreferencesVisual::getContrast() const
{
  return m_contrast;
}

/// Get the hue value.
KwMediaPreferencesVisual::Parameter KwMediaPreferencesVisual::getHue() const
{
  return m_hue;
}

/// Get the saturation value.
KwMediaPreferencesVisual::Parameter KwMediaPreferencesVisual::getSaturation() const
{
  return m_saturation;
}

/// Get the scale mode.
KwMediaPreferencesVisual::ScaleMode KwMediaPreferencesVisual::getScaleMode() const
{
  return m_scaleMode;
}

/*
 * Mutators
 */

/// Set the brightness value.
void KwMediaPreferencesVisual::setBrightness(Parameter brightness)
{
  m_brightness = brightness;
}

/// Set the contrast value.
void KwMediaPreferencesVisual::setContrast(Parameter contrast)
{
  m_contrast = contrast;
}

/// Set the hue value.
void KwMediaPreferencesVisual::setHue(Parameter hue)
{
  m_hue = hue;
}

/// Set the saturation value.
void KwMediaPreferencesVisual::setSaturation(Parameter saturation)
{
  m_saturation = saturation;
}

/// Set the scale mode.
void KwMediaPreferencesVisual::setScaleMode(ScaleMode scaleMode)
{
  m_scaleMode = scaleMode;
}

