#ifndef _KwMediaPreferencesVisual_h_
#define _KwMediaPreferencesVisual_h_

/**
 * @file KwMediaPreferencesVisual.h
 * @brief A media item's visual preferences.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractMediaPreferences.h"

#include <QtGlobal>

/// A media item's visual preferences.
/**
 * Basically this is visual based preferences such as brightness etc.
 */
class KwMediaPreferencesVisual : public KwAbstractMediaPreferences
{
  public:

    /*
     * Types
     */

    /// The type for visual parameters.
    typedef qreal Parameter;

    /// Scaling modes.
    enum ScaleMode
    {
      Unscaled,
      FitInView,
      Stretch,
      ScaleAndCrop
    };

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwMediaPreferencesVisual();

    /// Destructor.
    virtual ~KwMediaPreferencesVisual();

    /*
     * Accessors
     */

    /// Get the brightness value.
    Parameter getBrightness() const;

    /// Get the contrast value.
    Parameter getContrast() const;

    /// Get the hue value.
    Parameter getHue() const;

    /// Get the saturation value.
    Parameter getSaturation() const;

    /// Get the scale mode.
    ScaleMode getScaleMode() const;

    /*
     * Mutators
     */

    /// Set the brightness value.
    void setBrightness(Parameter brightness);

    /// Set the contrast value.
    void setContrast(Parameter contrast);

    /// Set the hue value.
    void setHue(Parameter hue);

    /// Set the saturation value.
    void setSaturation(Parameter saturation);

    /// Set the scale mode.
    void setScaleMode(ScaleMode scaleMode);

  private:

    /*
     * Variables
     */

    /// Brightness value.
    Parameter m_brightness;

    /// Contrast value.
    Parameter m_contrast;

    /// Hue value.
    Parameter m_hue;

    /// Saturation value.
    Parameter m_saturation;

    /// Scale mode.
    ScaleMode m_scaleMode;
};

#endif // _KwMediaPreferencesVisual_h_

