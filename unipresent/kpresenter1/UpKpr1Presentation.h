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

#ifndef _UpKpr1Presentation_h_
#define _UpKpr1Presentation_h_

/**
 * @file UpKpr1Presentation.h
 * @brief KPresenter 1 presentation.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpKpr1PresentationDcop.h"
#include "UpKpr1ViewDcop.h"
#include "UpPresentation.h"

class UpKpr1Backend;

/** KPresenter 1 presentation.
 * @todo We could do a lot more caching in this class to avoid repeated dcop
 *       terminal commands.
 */
class UpKpr1Presentation : public UpPresentation
{
  Q_OBJECT
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpKpr1Presentation(const UpKpr1PresentationDcop& dcop, const UpKpr1ViewDcop& dcopView, UpKpr1Backend* parent = 0);

    /// Destructor.
    virtual ~UpKpr1Presentation();

    /*
     * Main interface
     */

    virtual void close();
    virtual QUrl url() const;

    /*
     * Custom slideshows
     */

    virtual QString currentSlideshow();
    virtual QStringList slideshows();
    virtual void setSlideshow(QString slideshow);
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

    /*
     * Backend specific interface.
     */

    /// Get the dcop interface.
    UpKpr1PresentationDcop dcop() const;

    /// Get the dcop view interface.
    UpKpr1ViewDcop dcopView() const;

  private:

    /*
     * Variables
     */

    /// DCOP interface.
    UpKpr1PresentationDcop m_dcop;

    /// DCOP view interface.
    UpKpr1ViewDcop m_dcopView;

    /// Url.
    QUrl m_url;

    /*
     * Helpers
     */

    /// Signal that the slide has changed.
    void signalChangedSlide(int slide = -1, int step = -1);

    /// Signal that the step has changed.
    void signalChangedStep(int step = -1);
};

#endif // _UpKpr1Presentation_h_

