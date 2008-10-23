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

/**
 * @file UpKpr2Presentation.cpp
 * @brief KPresenter 2 presentation.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpKpr2Presentation.h"
#include "UpKpr2Slide.h"
#include "UpKpr2Backend.h"

#include <KLocale>

#include <QList>
#include <QVariant>
#include <QDBusReply>

#include <cassert>

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpKpr2Presentation::UpKpr2Presentation(QString service, QString path, UpKpr2Backend* backend, QObject* parent)
: UpPresentation(backend, parent)
, m_dbus(service, path, "org.kde.koffice.document")
, m_dbusView(0)
, m_url()
, m_customSlideshowsDialog(false)
{
  if (m_dbus.isValid())
  {
    m_url = m_dbus.call("url").arguments().first().toString();
    if ((QDBusReply<int>)m_dbus.call("viewCount") > 0)
    {
      QString viewPath = "/" + (QDBusReply<QString>)m_dbus.call("view", 0);
      m_dbusView = new QDBusInterface(service, viewPath, "org.kde.koffice.presentation.view");

      QDBusConnection::sessionBus().connect(service, viewPath, "org.kde.koffice.presentation.view", "activeCustomSlideShowChanged", this, SLOT(dbusCurrentSlideshowChanged(QString)));
      QDBusConnection::sessionBus().connect(service, viewPath, "org.kde.koffice.presentation.view", "customSlideShowsModified", this, SIGNAL(customSlideshowsModified()));

      QDBusConnection::sessionBus().connect(service, viewPath, "org.kde.koffice.presentation.view", "presentationStarted", this, SLOT(dbusScreenStarted(int)));
      QDBusConnection::sessionBus().connect(service, viewPath, "org.kde.koffice.presentation.view", "presentationStopped", this, SIGNAL(slideshowStopped()));

      QDBusConnection::sessionBus().connect(service, viewPath, "org.kde.koffice.presentation.view", "presentationPageChanged", this, SIGNAL(slideshowSlideChanged(int, int)));
      QDBusConnection::sessionBus().connect(service, viewPath, "org.kde.koffice.presentation.view", "presentationStepChanged", this, SIGNAL(slideshowStepChanged(int)));
    }
  }
}

/// Destructor.
UpKpr2Presentation::~UpKpr2Presentation()
{
  delete m_dbusView;
}

/*
 * Main interface
 */

void UpKpr2Presentation::close()
{
}

QUrl UpKpr2Presentation::url() const
{
  return m_url;
}

/*
 * Custom slideshows
 */

QString UpKpr2Presentation::currentSlideshow()
{
  if (m_dbusView)
  {
    QDBusReply<QString> result = m_dbusView->call("activeCustomSlideShow");
    if (result.isValid())
    {
      QString slideshow = result;
      if (!slideshow.isEmpty())
      {
        return slideshow;
      }
    }
  }
  return i18n("All slides");
}

QStringList UpKpr2Presentation::slideshows()
{
  QStringList results;
  results << i18n("All slides");
  if (m_dbusView)
  {
    QDBusReply<QStringList> reply = m_dbusView->call("customSlideShows");
    if (reply.isValid())
    {
      results << reply;
    }
  }
  return results;
}

void UpKpr2Presentation::setSlideshow(QString slideshow)
{
  if (slideshow == i18n("All slides"))
  {
    slideshow = QString();
  }
  if (m_dbusView)
  {
    m_dbusView->call("setActiveCustomSlideShow", slideshow);
  }
}

int UpKpr2Presentation::numSlides()
{
  if (m_dbusView)
  {
    QDBusReply<int> result = m_dbusView->call("numCustomSlideShowSlides");
    if (result.isValid())
    {
      return result;
    }
  }
  return 0;
}

UpSlide* UpKpr2Presentation::slide(int index)
{
  return new UpKpr2Slide(this, index);
}

/*
 * Slideshow accessors
 */

bool UpKpr2Presentation::isSlideshowRunning()
{
  if (m_dbusView)
  {
    QDBusReply<bool> result = m_dbusView->call("isPresentationRunning");
    if (result.isValid())
    {
      return result;
    }
  }
  return false;
}

int UpKpr2Presentation::numSlidesInSlideshow()
{
  if (m_dbusView)
  {
    QDBusReply<int> result = m_dbusView->call("numPresentationPages");
    if (result.isValid())
    {
      // There's also the finish slide
      /// @todo the finish slide is optional, ensure this is correct
      return result - 1;
    }
  }
  return 0;
}

int UpKpr2Presentation::currentSlideshowSlide()
{
  if (m_dbusView)
  {
    QDBusReply<int> result = m_dbusView->call("currentPresentationPage");
    if (result.isValid())
    {
      return result;
    }
  }
  return 0;
}

int UpKpr2Presentation::stepsInCurrentSlideshowSlide()
{
  if (m_dbusView)
  {
    QDBusReply<int> result = m_dbusView->call("numStepsInPresentationPage");
    if (result.isValid())
    {
      int steps = result;
      if (steps <= 0)
      {
        steps = 1;
      }
      return steps;
    }
  }
  return 1;
}

int UpKpr2Presentation::currentSlideshowStep()
{
  if (m_dbusView)
  {
    QDBusReply<int> result = m_dbusView->call("currentPresentationStep");
    if (result.isValid())
    {
      return result;
    }
  }
  return 0;
}

/*
 * Slideshow control
 */

void UpKpr2Presentation::startSlideshow()
{
  if (m_dbusView)
  {
    m_dbusView->call("presentationStart");
  }
}

void UpKpr2Presentation::stopSlideshow()
{
  if (m_dbusView)
  {
    m_dbusView->call("presentationStop");
  }
}

void UpKpr2Presentation::goToSlide(int index)
{
  if (m_dbusView)
  {
    m_dbusView->call("gotoPresentationPage", index);
  }
}

void UpKpr2Presentation::previousSlide()
{
  if (m_dbusView)
  {
    m_dbusView->call("presentationPrevSlide");
  }
}

void UpKpr2Presentation::nextSlide()
{
  if (m_dbusView)
  {
    m_dbusView->call("presentationNextSlide");
  }
}

void UpKpr2Presentation::previousStep()
{
  if (m_dbusView)
  {
    m_dbusView->call("presentationPrev");
  }
}

void UpKpr2Presentation::nextStep()
{
  if (m_dbusView)
  {
    m_dbusView->call("presentationNext");
  }
}

/*
 * Backend specific interface.
 */

/// Get the dbus interface.
QDBusInterface& UpKpr2Presentation::dbus()
{
  return m_dbus;
}

/// Get the dbus view interface.
QDBusInterface* UpKpr2Presentation::dbusView()
{
  return m_dbusView;
}

/*
 * DBus slots
 */

void UpKpr2Presentation::dbusCurrentSlideshowChanged(QString slideshow)
{
  if (slideshow.isEmpty())
  {
    slideshow = i18n("All slides");
  }
  currentSlideshowChanged(slideshow);
}

void UpKpr2Presentation::dbusScreenStarted(int pages)
{
  /// @todo find whether this incldues the finish page or not
  slideshowStarted(pages-1);
}

/*
 * Callbacks
 */

void UpKpr2Presentation::callbackResult()
{
  m_customSlideshowsDialog = false;
}

void UpKpr2Presentation::callbackError()
{
  m_customSlideshowsDialog = false;
}

#include "UpKpr2Presentation.moc"

