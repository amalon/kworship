#ifndef _KwMediaPreferencesAudio_h_
#define _KwMediaPreferencesAudio_h_

/**
 * @file KwMediaPreferencesAudio.h
 * @brief A media item's audio preferences.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractMediaPreferences.h"

#include <QtGlobal>

/// A media item's audio preferences.
/**
 * Basically this is audio preferences such as volume, muted, fadeout time.
 */
class KwMediaPreferencesAudio : public KwAbstractMediaPreferences
{
  public:

    /*
     * Types
     */

    /// Time interval type.
    typedef qint32 TimeInterval;

    /// Volume level type.
    typedef qreal Volume;

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwMediaPreferencesAudio();

    /// Destructor.
    virtual ~KwMediaPreferencesAudio();

    /*
     * Accessors
     */

    /// Get the volume level.
    Volume getVolume() const;

    /// Get whether the audio is muted.
    bool getMuted() const;

    /// Get the fadeout time in msecs.
    TimeInterval getFadeoutMsec() const;

    /*
     * Mutators
     */

    /// Set the volume level.
    void setVolume(Volume volume);

    /// Set whether the audio is muted.
    void setMuted(bool muted);

    /// Set the fadeout time in msecs.
    void setFadeoutMsec(TimeInterval fadeoutMsec);

  private:

    /*
     * Variables
     */

    /// Volume level.
    Volume m_volume;

    /// Whether the sound is muted.
    bool m_muted;

    /// Audio fadeout time in msec.
    TimeInterval m_fadeoutMsec;

};

#endif // _KwMediaPreferencesAudio_h_

