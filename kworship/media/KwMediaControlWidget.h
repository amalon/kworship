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

#ifndef _KwMediaControlWidget_h_
#define _KwMediaControlWidget_h_

/**
 * @file KwMediaControlWidget.h
 * @brief Controls the preferences of the currently playing media items.
 * @author James Hogan <james@albanarts.com>
 */

#include <QWidget>

class KwMediaManager;
class KwMediaControlWidgetSequence;
class KwMediaControlWidgetAudio;
class KwMediaControlWidgetVisual;

/// Controls the preferences of the currently playing media items.
class KwMediaControlWidget : public QWidget
{
    Q_OBJECT
  public:

    /*
     * Constructors + destructors
     */

    /// Primary constructor.
    KwMediaControlWidget(KwMediaManager* manager, QWidget* parent);

    /// Destructor.
    virtual ~KwMediaControlWidget();

  public slots:

    /*
     * Slots
     */

    /// Audio has been added.
    void addAudio(bool linkedVideo);
    /// Video has been added.
    void addVideo(bool linkedAudio);

    /// Audio has been removed.
    void removeAudio(bool removeLinkedVideo);
    /// Video has been removed.
    void removeVideo(bool removeLinkedAudio);

  private:

    /*
     * Variables
     */

    /// Manager to control.
    KwMediaManager* m_manager;

    /// Audio sequencer.
    KwMediaControlWidgetSequence* m_audioSequencer;

    /// Video sequencer.
    KwMediaControlWidgetSequence* m_videoSequencer;

    /// Audio control.
    KwMediaControlWidgetAudio* m_audio;

    /// Visual control.
    KwMediaControlWidgetVisual* m_visual;
};

#endif // _KwMediaControlWidget_h_

