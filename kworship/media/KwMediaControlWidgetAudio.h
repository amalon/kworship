/***************************************************************************
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   This file is part of KWorship.                                        *
 *                                                                         *
 *   KWorship is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   KWorship is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with KWorship.  If not, see <http://www.gnu.org/licenses/>.     *
 ***************************************************************************/

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

