#ifndef _KwMediaControlWidgetVisual_h_
#define _KwMediaControlWidgetVisual_h_

/**
 * @file KwMediaControlWidgetVisual.h
 * @brief Controls visual preferences of playing media items.
 * @author James Hogan <james@albanarts.com>
 */

#include <QWidget>

class KwMediaManager;

class QSlider;

/// Controls visual preferences of playing media items.
class KwMediaControlWidgetVisual : public QWidget
{
    Q_OBJECT
  public:

    /*
     * Constructors + destructors
     */

    /// Primary constructor.
    KwMediaControlWidgetVisual(KwMediaManager* manager, QWidget* parent);

    /// Destructor.
    virtual ~KwMediaControlWidgetVisual();

  public slots:

    /*
     * Public slots
     */

  signals:

    /*
     * Signals
     */

  private slots:

    /*
     * Private slots
     */

  private:

    /*
     * Variables
     */

    /// Manager to control.
    KwMediaManager* m_manager;
};

#endif // _KwMediaControlWidgetVisual_h_

