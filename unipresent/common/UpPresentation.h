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

#ifndef _UpPresentation_h_
#define _UpPresentation_h_

/**
 * @file UpPresentation.h
 * @brief An abstract presentation document.
 * @author James Hogan <james@albanarts.com>
 */

#include <kdemacros.h>

#include <QObject>
#include <QUrl>

class UpSlide;
class UpBackend;

/** An abstract presentation document.
 * Inherit from this class to implement each backend's presentation.
 */
class KDE_EXPORT UpPresentation : public QObject
{
  Q_OBJECT
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpPresentation(UpBackend* backend, QObject* parent = 0);

    /// Destructor.
    virtual ~UpPresentation();

    /*
     * Accessors
     */

    /// Get the backend.
    UpBackend* backend();

    /*
     * Main interface
     */

    /// Close this presentation.
    virtual void close() = 0;

    /// Get the url.
    virtual QUrl url() const = 0;

    /*
     * Custom slideshows
     */

    /// Get the current slideshow name.
    virtual QString currentSlideshow() = 0;

    /// Get a list of slideshow names.
    virtual QStringList slideshows() = 0;

    /// Set the current slideshow.
    virtual void setSlideshow(QString slideshow) = 0;

    /// Get the number of slides in the current slideshow.
    virtual int numSlides() = 0;

    /// Get a specific slide from the current slideshow.
    virtual UpSlide* slide(int index) = 0;

    /*
     * Slideshow accessors
     */

    /// Find whether the slideshow is running.
    virtual bool isSlideshowRunning() = 0;

    /// Find the number of slides in the slideshow.
    virtual int numSlidesInSlideshow() = 0;

    /// Find the current slide number.
    virtual int currentSlideshowSlide() = 0;

    /// Find the number of steps in the current slide.
    virtual int stepsInCurrentSlideshowSlide() = 0;

    /// Find the current step within the slide.
    virtual int currentSlideshowStep() = 0;

    /*
     * Slideshow control
     */

    /// Start the slideshow.
    virtual void startSlideshow() = 0;

    /// Stop the slideshow.
    virtual void stopSlideshow() = 0;

    /// Go to a specific slide.
    virtual void goToSlide(int index) = 0;

    /// Go back to the previous slide.
    virtual void previousSlide() = 0;

    /// Go on to the next slide.
    virtual void nextSlide() = 0;

    /// Go back to the previous step.
    virtual void previousStep() = 0;

    /// Trigger the next step.
    virtual void nextStep() = 0;

  signals:

    /*
     * Signals
     */

    /// Fired when the current slideshow is changed.
    void currentSlideshowChanged(QString slideshow);

    /// Fired when custom slideshows have been modified.
    void customSlideshowsModified();


    /// Fired when the slideshow starts.
    void slideshowStarted(int numSlides);

    /// Fired when the slideshow stops.
    void slideshowStopped();

    /// Fired when the current slide changes.
    void slideshowSlideChanged(int slide, int numSteps);

    /// Fired when the current step changes.
    void slideshowStepChanged(int step);

  private:

    /*
     * Variables
     */

    /// Backend this presentation is associated with.
    UpBackend* m_backend;
};

#endif // _UpPresentation_h_

