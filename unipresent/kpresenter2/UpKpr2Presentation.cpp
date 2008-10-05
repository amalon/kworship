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

#include <QList>
#include <QVariant>

#include <cassert>

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpKpr2Presentation::UpKpr2Presentation(QString service, QString path, QObject* parent)
: UpPresentation(parent)
, m_dbus(service, path, "org.kde.koffice.document")
, m_dbusView(0)
, m_url()
, m_customSlideshowsDialog(false)
{
  if (m_dbus.isValid())
  {
    m_url = m_dbus.call("url").arguments().first().toString();
    QString viewPath = "/" + m_dbus.call("view", 0).arguments().first().toString();
    m_dbusView = new QDBusInterface(service, viewPath, "org.kde.koffice.kpresenter.view");

    QDBusConnection::sessionBus().connect(service, viewPath, "org.kde.koffice.kpresenter.view", "activeCustomSlideShowChanged", this, SLOT(dbusCurrentSlideshowChanged(QString)));
    QDBusConnection::sessionBus().connect(service, viewPath, "org.kde.koffice.kpresenter.view", "customSlideShowsModified", this, SIGNAL(customSlideshowsModified()));

    QDBusConnection::sessionBus().connect(service, viewPath, "org.kde.koffice.kpresenter.view", "screenStarted", this, SLOT(dbusScreenStarted(int)));
    QDBusConnection::sessionBus().connect(service, viewPath, "org.kde.koffice.kpresenter.view", "screenStopped", this, SIGNAL(slideshowStopped()));

    QDBusConnection::sessionBus().connect(service, viewPath, "org.kde.koffice.kpresenter.view", "changedPresPage", this, SIGNAL(slideshowSlideChanged(int, int)));
    QDBusConnection::sessionBus().connect(service, viewPath, "org.kde.koffice.kpresenter.view", "changedPresStep", this, SIGNAL(slideshowStepChanged(int)));
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
    QDBusMessage result = m_dbusView->call("activeCustomSlideShow");
    if (QDBusMessage::ReplyMessage == result.type())
    {
      QString slideshow = result.arguments().first().toString();
      if (slideshow != "")
      {
        return slideshow;
      }
    }
  }
  return tr("All slides");
}

QStringList UpKpr2Presentation::slideshows()
{
  QStringList results;
  results << tr("All slides");
  if (m_dbusView)
  {
    QDBusMessage reply = m_dbusView->call("customSlideShows");
    if (QDBusMessage::ReplyMessage == reply.type())
    {
      results << reply.arguments().first().toStringList();
    }
  }
  return results;
}

void UpKpr2Presentation::setSlideshow(QString slideshow)
{
  if (slideshow == tr("All slides"))
  {
    slideshow = QString();
  }
  if (m_dbusView)
  {
    m_dbusView->call("setActiveCustomSlideShow", slideshow);
  }
}

void UpKpr2Presentation::editCustomSlideshowsDialog()
{
  if (m_dbusView && !m_customSlideshowsDialog)
  {
    m_customSlideshowsDialog = true;
    m_dbusView->callWithCallback("editCustomSlideShowsDialog", QList<QVariant>(), this, SLOT(callbackResult()), SLOT(callbackError()));
  }
}

int UpKpr2Presentation::numSlides()
{
  return 0;
}

UpSlide* UpKpr2Presentation::slide(int index)
{
  return 0;
}

/*
 * Slideshow accessors
 */

bool UpKpr2Presentation::isSlideshowRunning()
{
  return false;
}

int UpKpr2Presentation::numSlidesInSlideshow()
{
  if (m_dbusView)
  {
    QDBusMessage result = m_dbusView->call("numPresPages");
    if (QDBusMessage::ReplyMessage == result.type())
    {
      // There's also the finish slide
      /// @todo the finish slide is optional, ensure this is correct
      int slides = result.arguments().first().toInt() - 1;
      return slides;
    }
  }
  return 0;
}

int UpKpr2Presentation::currentSlideshowSlide()
{
  if (m_dbusView)
  {
    QDBusMessage result = m_dbusView->call("currentPresPage");
    if (QDBusMessage::ReplyMessage == result.type())
    {
      int slide = result.arguments().first().toInt();
      return slide;
    }
  }
  return 0;
}

int UpKpr2Presentation::stepsInCurrentSlideshowSlide()
{
  if (m_dbusView)
  {
    QDBusMessage result = m_dbusView->call("numStepsInPresPage");
    if (QDBusMessage::ReplyMessage == result.type())
    {
      int steps = result.arguments().first().toInt();
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
    QDBusMessage result = m_dbusView->call("currentPresStep");
    if (QDBusMessage::ReplyMessage == result.type())
    {
      return result.arguments().first().toInt();
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
    m_dbusView->call("screenStart");
  }
}

void UpKpr2Presentation::stopSlideshow()
{
  if (m_dbusView)
  {
    m_dbusView->call("screenStop");
  }
}

void UpKpr2Presentation::goToSlide(int index)
{
}

void UpKpr2Presentation::previousSlide()
{
  if (m_dbusView)
  {
    m_dbusView->call("screenPrevSlide");
  }
}

void UpKpr2Presentation::nextSlide()
{
  if (m_dbusView)
  {
    m_dbusView->call("screenNextSlide");
  }
}

void UpKpr2Presentation::previousStep()
{
  if (m_dbusView)
  {
    m_dbusView->call("screenPrev");
  }
}

void UpKpr2Presentation::nextStep()
{
  if (m_dbusView)
  {
    m_dbusView->call("screenNext");
  }
}

/*
 * DBus slots
 */

void UpKpr2Presentation::dbusCurrentSlideshowChanged(QString slideshow)
{
  if (slideshow == "")
  {
    slideshow = tr("All slides");
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

