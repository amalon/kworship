#ifndef _KwMediaControlWidgetAudio_h_
#define _KwMediaControlWidgetAudio_h_

/**
 * @file KwMediaControlWidgetAudio.h
 * @brief Controls audio preferences of playing media items.
 * @author James Hogan <james@albanarts.com>
 */

#include <QWidget>

class KwMediaManager;

class QSlider;
class QCheckBox;

/// Controls audio preferences of playing media items.
class KwMediaControlWidgetAudio : public QWidget
{
    Q_OBJECT
  public:

    /*
     * Constructors + destructors
     */

    /// Primary constructor.
    KwMediaControlWidgetAudio(KwMediaManager* manager, QWidget* parent);

    /// Destructor.
    virtual ~KwMediaControlWidgetAudio();

  public slots:

    /*
     * Public slots
     */

    /// Set volume.
    void setVolume(qreal volume);

  signals:

    /*
     * Signals
     */

    /// Muted has changed.
    void mutedChanged(bool muted);

    /// Volume has changed.
    void volumeChanged(qreal volume);

  private slots:

    /*
     * Private slots
     */

    /// The volume slider has moved.
    void volumeSliderMoved(int value);

  private:

    /*
     * Variables
     */

    /// Manager to control.
    KwMediaManager* m_manager;

    /// Mute checkbox.
    QCheckBox* m_chkMuted;

    /// Volume slider.
    QSlider* m_sliderVolume;
};

#endif // _KwMediaControlWidgetAudio_h_

