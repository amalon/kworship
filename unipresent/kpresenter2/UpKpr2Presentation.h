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

#ifndef _UpKpr2Presentation_h_
#define _UpKpr2Presentation_h_

/**
 * @file UpKpr2Presentation.h
 * @brief KPresenter 2 presentation.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpPresentation.h"

/// KPresenter 2 presentation.
class UpKpr2Presentation : public UpPresentation
{
  Q_OBJECT
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpKpr2Presentation(QObject* parent = 0);

    /// Destructor.
    virtual ~UpKpr2Presentation();

    /*
     * Main interface
     */

    virtual void close();

    virtual QUrl url() const;

    /*
     * Slides
     */

    virtual int numSlides();

    virtual UpSlide* slide(int index);

    /*
     * Slideshow accessors
     */

    virtual bool isSlideshowRunning();

    virtual int numSlidesInSlideshow();

    virtual int currentSlideshowSlide();

    virtual int stepsInCurrentSlideshowSlide();

    virtual int currentSlideshowStep();

    /*
     * Slideshow control
     */

    virtual void startSlideshow();

    virtual void stopSlideshow();

    virtual void goToSlide(int index);

    virtual void previousSlide();

    virtual void nextSlide();

    virtual void previousStep();

    virtual void nextStep();

  private:

    /*
     * Variables
     */

    /// Url.
    QUrl m_url;
};

#endif // _UpKpr2Presentation_h_

