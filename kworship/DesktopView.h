/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   KWorship is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   KWorship is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with KWorship.  If not, write to the Free Software Foundation,  *
 *   Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.   *
 ***************************************************************************/

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

