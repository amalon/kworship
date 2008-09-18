#ifndef _DesktopView_h_
#define _DesktopView_h_

/**
 * @file DesktopView.h
 * @brief Preview of the screens on the desktop.
 * @author James Hogan <james@albanarts.com>
 */

#include <QGraphicsView>
#include <QVector>

/** Screens preview widget.
 * @todo Ensure works well with out of range screen id in multiselect mode
 */
class DesktopView : public QGraphicsView
{
  Q_OBJECT
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    DesktopView(QWidget* parent);

    /// Destructor.
    ~DesktopView();

    /*
     * Properties
     */

    Q_PROPERTY(int selectedScreen READ selectedScreen WRITE setSelectedScreen)

    /*
     * Main interface
     */

    /// Find whether a screen is selected.
    bool isScreenSelected(int screen) const;

    /// Find which single screen is selected.
    int selectedScreen() const;

  public slots:

    /*
     * Public slots
     */

    /// Set the selected screen.
    void setSelectedScreen(int selectedScreen);

  signals:

    /*
     * Public signals
     */

    /// A screen selection has changed.
    void screenSelected(int screen, bool selected);

    /// Current single select screen has changed.
    void screenChanged(int screen);

    /// Status message has changed.
    void statusChanged(QString status);

  protected:

    /*
     * Events
     */

    void resizeEvent(QResizeEvent*);

    void mousePressEvent(QMouseEvent* event);

  private slots:

    /*
     * Private slots
     */

    /// Indicates that a screen has been resized.
    void resizeScreen(int screen);

  private:
  
    /*
     * Variables
     */

    /// Desktop rectangle size.
    QRectF m_desktopRect;

    /// Whether to allow multiple screens to be selected.
    bool m_multiSelect;

    /// Whether to allow no screen to be selected.
    bool m_noSelect;

    /// Which screen is selected when in singleselect.
    int m_selectedScreen;

    /// Which screens are selected when in multiselect.
    QVector<bool> m_selectedScreens;

    /*
     * Private functions
     */

    /// Setup the display.
    void setup();

    /// Change selection of a screen.
    void selectScreen(int screen, bool newSelected);

    /// Update a single selection status.
    void singleSelectRestatus();
};

#endif // _DesktopView_h_

