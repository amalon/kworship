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

#include <QDBusInterface>

class UpKpr2Backend;

/// KPresenter 2 presentation.
class UpKpr2Presentation : public UpPresentation
{
  Q_OBJECT
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpKpr2Presentation(QString service, QString path, UpKpr2Backend* backend, QObject* parent = 0);

    /// Destructor.
    virtual ~UpKpr2Presentation();

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

    /// Get the dbus view interface.
    QDBusInterface* dbusView();

  private slots:

    /*
     * DBus slots
     */

    void dbusCurrentSlideshowChanged(QString slideshow);
    void dbusScreenStarted(int pages);

    /*
     * Callbacks
     */

    void callbackResult();
    void callbackError();

  private:

    /*
     * Variables
     */

    /// DBus document interface.
    QDBusInterface m_dbus;

    /// DBus view interface.
    QDBusInterface* m_dbusView;

    /// Url.
    QUrl m_url;

    /// Whether the custom slideshows dialog is being opened.
    bool m_customSlideshowsDialog;
};

#endif // _UpKpr2Presentation_h_

