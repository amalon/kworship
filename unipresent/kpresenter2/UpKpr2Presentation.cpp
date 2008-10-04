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
{
  if (m_dbus.isValid())
  {
    m_url = m_dbus.call("url").arguments().first().toString();
    QString viewPath = "/" + m_dbus.call("view", 0).arguments().first().toString();
    m_dbusView = new QDBusInterface(service, viewPath, "org.kde.koffice.kpresenter.view");
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
    m_dbusView->call("screenStartFromFirst");
    slideshowStarted(numSlidesInSlideshow());
    slideshowSlideChanged(currentSlideshowSlide(), stepsInCurrentSlideshowSlide());
    slideshowStepChanged(currentSlideshowStep());
  }
}

void UpKpr2Presentation::stopSlideshow()
{
  if (m_dbusView)
  {
    m_dbusView->call("screenStop");
    slideshowStopped();
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
    slideshowSlideChanged(currentSlideshowSlide(), stepsInCurrentSlideshowSlide());
    slideshowStepChanged(currentSlideshowStep());
  }
}

void UpKpr2Presentation::nextSlide()
{
  if (m_dbusView)
  {
    m_dbusView->call("screenNextSlide");
    slideshowSlideChanged(currentSlideshowSlide(), stepsInCurrentSlideshowSlide());
    slideshowStepChanged(currentSlideshowStep());
  }
}

void UpKpr2Presentation::previousStep()
{
  if (m_dbusView)
  {
    m_dbusView->call("screenPrev");
    slideshowSlideChanged(currentSlideshowSlide(), stepsInCurrentSlideshowSlide());
    slideshowStepChanged(currentSlideshowStep());
  }
}

void UpKpr2Presentation::nextStep()
{
  if (m_dbusView)
  {
    m_dbusView->call("screenNext");
    slideshowSlideChanged(currentSlideshowSlide(), stepsInCurrentSlideshowSlide());
    slideshowStepChanged(currentSlideshowStep());
  }
}

#include "UpKpr2Presentation.moc"

