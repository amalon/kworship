/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008-2009 James Hogan <james@albanarts.com>                 *
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

#ifndef _UpOkPresentation_h_
#define _UpOkPresentation_h_

/**
 * @file UpOkPresentation.h
 * @brief Okular presentation.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpPresentation.h"

#include <QDBusInterface>

class UpOkBackend;

/// Okular presentation.
class UpOkPresentation : public UpPresentation
{
  Q_OBJECT
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpOkPresentation(QString service, UpOkBackend* backend, QObject* parent = 0);

    /// Destructor.
    virtual ~UpOkPresentation();

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

    /// Get the dbus interface.
    QDBusInterface& dbus();

  private:

    /*
     * Variables
     */

    /// Main DBus interface.
    QDBusInterface m_dbus;

    /// Url.
    QUrl m_url;

    /// Slideshow running.
    bool m_running;
};

#endif // _UpOkPresentation_h_

