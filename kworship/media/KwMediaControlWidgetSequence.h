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

