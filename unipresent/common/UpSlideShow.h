/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
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

#ifndef _UpSlideShow_h_
#define _UpSlideShow_h_

/**
 * @file UpSlideShow.h
 * @brief An abstract slideshow controller.
 * @author James Hogan <james@albanarts.com>
 */

#include <QObject>

class UpSlide;

/** An abstract slideshow controller.
 * Inherit from this class to implement each backend's slideshow controller.
 */
class UpSlideShow : public QObject
{
  Q_OBJECT
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpSlideShow(QObject* parent = 0);

    /// Destructor.
    virtual ~UpSlideShow();

    /*
     * Main interface
     */

    /// Start the slideshow.
    virtual void start() = 0;

    /// Stop the slideshow.
    virtual void stop() = 0;

    /// Pause the slideshow.
    virtual void pause() = 0;

    /// Resume the slideshow.
    virtual void resume() = 0;

    /// Go to the next part of the slideshow.
    virtual void next() = 0;

    /// Go to the previous part of the slideshow.
    virtual void previous() = 0;

  signals:

    /*
     * Signals
     */

    /// The slideshow has changed slide.
    void changedSlide(UpSlide* previousSlide, UpSlide* currentSlide);

    /// The current slide has been updated.
    void updatedSlide(UpSlide* slide);
};

#endif // _UpSlideShow_h_

