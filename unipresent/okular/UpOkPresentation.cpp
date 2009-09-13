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

/**
 * @file UpOkPresentation.cpp
 * @brief Okular presentation.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpOkPresentation.h"
#include "UpOkSlide.h"
#include "UpOkBackend.h"

#include <KLocale>

#include <QList>
#include <QVariant>
#include <QDBusReply>

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpOkPresentation::UpOkPresentation(QString service, UpOkBackend* backend, QObject* parent)
: UpPresentation(backend, parent)
, m_dbus(service, "/okular", "org.kde.okular")
, m_url()
, m_running(false)
{
  if (m_dbus.isValid())
  {
    m_url = m_dbus.call("currentDocument").arguments().first().toString();
  }
}

/// Destructor.
UpOkPresentation::~UpOkPresentation()
{
}

/*
 * Main interface
 */

void UpOkPresentation::close()
{
}

QUrl UpOkPresentation::url() const
{
  return m_url;
}

/*
 * Custom slideshows
 */

QString UpOkPresentation::currentSlideshow()
{
  return i18n("All slides");
}

QStringList UpOkPresentation::slideshows()
{
  QStringList results;
  results << i18n("All slides");
  return results;
}

void UpOkPresentation::setSlideshow(QString slideshow)
{
}

int UpOkPresentation::numSlides()
{
  QDBusReply<unsigned int> result = m_dbus.call("pages");
  if (result.isValid())
  {
    return (int)result;
  }
  return 0;
}

UpSlide* UpOkPresentation::slide(int index)
{
  return new UpOkSlide(this, index);
}

/*
 * Slideshow accessors
 */

bool UpOkPresentation::isSlideshowRunning()
{
  return m_running;
}

int UpOkPresentation::numSlidesInSlideshow()
{
  return numSlides();
}

int UpOkPresentation::currentSlideshowSlide()
{
  QDBusReply<unsigned int> result = m_dbus.call("currentPage");
  if (result.isValid())
  {
    return result-1;
  }
  return 0;
}

int UpOkPresentation::stepsInCurrentSlideshowSlide()
{
  return 1;
}

int UpOkPresentation::currentSlideshowStep()
{
  return 0;
}

/*
 * Slideshow control
 */

void UpOkPresentation::startSlideshow()
{
  if (!m_running)
  {
    m_dbus.call("slotTogglePresentation");
    emit slideshowStarted(numSlides());
    emit slideshowSlideChanged(currentSlideshowSlide(), 1);
    emit slideshowStepChanged(0);
    m_running = true;
  }
}

void UpOkPresentation::stopSlideshow()
{
  if (m_running)
  {
    m_dbus.call("slotTogglePresentation");
    emit slideshowStopped();
    m_running = false;
  }
}

void UpOkPresentation::goToSlide(int index)
{
  m_dbus.call("goToPage", (unsigned int)index+1);
  if (m_running)
  {
    emit slideshowSlideChanged(currentSlideshowSlide(), 1);
    emit slideshowStepChanged(0);
  }
}

void UpOkPresentation::previousSlide()
{
  m_dbus.call("slotPreviousPage");
  emit slideshowSlideChanged(currentSlideshowSlide(), 1);
  emit slideshowStepChanged(0);
}

void UpOkPresentation::nextSlide()
{
  m_dbus.call("slotNextPage");
  emit slideshowSlideChanged(currentSlideshowSlide(), 1);
  emit slideshowStepChanged(0);
}

void UpOkPresentation::previousStep()
{
  previousSlide();
}

void UpOkPresentation::nextStep()
{
  nextSlide();
}

/*
 * Backend specific interface.
 */

/// Get the dbus interface.
QDBusInterface& UpOkPresentation::dbus()
{
  return m_dbus;
}

#include "UpOkPresentation.moc"

