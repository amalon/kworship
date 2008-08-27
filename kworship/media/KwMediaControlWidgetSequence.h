#ifndef _KwMediaControlWidgetSequence_h_
#define _KwMediaControlWidgetSequence_h_

/**
 * @file KwMediaControlWidgetSequence.h
 * @brief Controls sequence of playing media items.
 * @author James Hogan <james@albanarts.com>
 */

#include <phonon/phononnamespace.h>

#include <QWidget>

class KwMediaManager;

class QPushButton;
class QLabel;

/// Controls sequence of playing media items.
class KwMediaControlWidgetSequence : public QWidget
{
    Q_OBJECT
  public:

    /*
     * Constructors + destructors
     */

    /// Primary constructor.
    KwMediaControlWidgetSequence(KwMediaManager* manager, QWidget* parent);

    /// Destructor.
    virtual ~KwMediaControlWidgetSequence();

  public slots:

    /*
     * Slots
     */

    /// Change the state of the media.
    void changeState(Phonon::State newState, Phonon::State oldState);

    /// Set the name of the media.
    void setMediaName(QString name);

  signals:

    /*
     * Signals
     */

    /// Fired when play/pause is clicked.
    void playPause();

    /// Fired when stop is clocked.
    void stop();

  private:

    /*
     * Variables
     */

    /// Manager to control.
    KwMediaManager* m_manager;

    /// Pause button.
    QPushButton* m_btnPlayPause;

    /// Stop button.
    QPushButton* m_btnStop;

    /// Media name label.
    QLabel* m_lblTitle;
};

#endif // _KwMediaControlWidgetSequence_h_

