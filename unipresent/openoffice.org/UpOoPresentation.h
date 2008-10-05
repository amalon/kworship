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

#ifndef _UpOoPresentation_h_
#define _UpOoPresentation_h_

/**
 * @file UpOoPresentation.h
 * @brief OpenOffice.org presentation.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpPresentation.h"

#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/uno/XInterface.hpp>

using namespace com::sun::star;

/// OpenOffice.org presentation.
class UpOoPresentation : public UpPresentation
{
  Q_OBJECT
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpOoPresentation(uno::XInterface* interface, QObject* parent = 0);

    /// Destructor.
    virtual ~UpOoPresentation();

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
    virtual void editCustomSlideshowsDialog();
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

    /// An interface to the document.
    uno::Reference<uno::XInterface> m_interface;

    /// The file's URL.
    QUrl m_url;
};

#endif // _UpOoPresentation_h_

