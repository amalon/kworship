#ifndef _KwMediaPreferencesAudio_h_
#define _KwMediaPreferencesAudio_h_

/**
 * @file KwMediaPreferencesAudio.h
 * @brief A media item's audio preferences.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractMediaPreferences.h"

/// A media item's audio preferences.
/**
 * Basically this is audio preferences such as volume, muted, fadeout time.
 */
class KwMediaPreferencesAudio : public KwAbstractMediaPreferences
{
    Q_OBJECT
  public:

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
    qreal getVolume() const;

    /// Get whether the audio is muted.
    bool getMuted() const;

    /// Get the fadeout time in msecs.
    qint32 getFadeoutMsec() const;

  public slots:

    /*
     * Slots
     */

    /// Set the volume level.
    void setVolume(qreal volume);

    /// Set whether the audio is muted.
    void setMuted(bool muted);

    /// Set the fadeout time in msecs.
    void setFadeoutMsec(qint32 fadeoutMsec);

  signals:

    /*
     * Signals
     */

    /// Volume level has changed.
    void volumeChanged(qreal newVolume);

    /// Muted has changed.
    void mutedChanged(bool muted);

  private:

    /*
     * Variables
     */

    /// Volume level.
    qreal m_volume;

    /// Whether the sound is muted.
    bool m_muted;

    /// Audio fadeout time in msec.
    qint32 m_fadeoutMsec;

};

#endif // _KwMediaPreferencesAudio_h_

