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
 * @file UpOoPresentation.cpp
 * @brief OpenOffice.org presentation.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpOoPresentation.h"
#include "UpOoSlide.h"
#include "UpOoBackend.h"

#include <com/sun/star/container/XIndexAccess.hpp>
#include <com/sun/star/drawing/XDrawPagesSupplier.hpp>
#include <com/sun/star/drawing/XDrawPages.hpp>
#include <com/sun/star/drawing/XDrawPage.hpp>
#include <com/sun/star/frame/XModel.hpp>
#include <com/sun/star/presentation/XPresentationSupplier.hpp>
#include <com/sun/star/presentation/XPresentation.hpp>
#include <com/sun/star/presentation/XPresentation2.hpp>
#include <com/sun/star/presentation/XSlideShowController.hpp>

#include <QtGlobal>

using namespace com::sun::star::drawing;
using namespace com::sun::star::frame;
using namespace com::sun::star::presentation;
using namespace com::sun::star::uno;

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpOoPresentation::UpOoPresentation(uno::XInterface* interface, UpOoBackend* parent)
: UpPresentation(parent)
, m_interface(interface)
, m_url()
{
  // Get the url
  Reference<XModel> model(interface, UNO_QUERY);
  Q_ASSERT(0 != model.get());
  m_url = QString::fromUtf16((const sal_Unicode*)model->getURL());
}

/// Destructor.
UpOoPresentation::~UpOoPresentation()
{
}

/*
 * Main interface
 */

void UpOoPresentation::close()
{
}

QUrl UpOoPresentation::url() const
{
  return m_url;
}

/*
 * Custom slideshows
 */

QString UpOoPresentation::currentSlideshow()
{
  // see presentation::CustomShow
  return "All slides";
}

QStringList UpOoPresentation::slideshows()
{
  // see presentation::CustomPresentation
  return QStringList() << "All slides";
}

void UpOoPresentation::setSlideshow(QString slideshow)
{
}

int UpOoPresentation::numSlides()
{
  Reference<XDrawPagesSupplier> drawPagesSupplier(m_interface, UNO_QUERY);
  Q_ASSERT(0 != drawPagesSupplier.get());
  Reference<XDrawPages> drawPages = drawPagesSupplier->getDrawPages();
  return drawPages->getCount();
}

UpSlide* UpOoPresentation::slide(int index)
{
  Reference<XDrawPagesSupplier> drawPagesSupplier(m_interface, UNO_QUERY);
  Q_ASSERT(0 != drawPagesSupplier.get());
  Reference<XDrawPages> drawPages = drawPagesSupplier->getDrawPages();
  Reference<XDrawPage> drawPage(drawPages->getByIndex(index), UNO_QUERY);
  return new UpOoSlide(drawPage.get(), this);
}

/*
 * Slideshow accessors
 */

bool UpOoPresentation::isSlideshowRunning()
{
  Reference<XPresentationSupplier> presentationSupplier(m_interface, UNO_QUERY);
  Reference<XPresentation2> presentation(presentationSupplier->getPresentation(),UNO_QUERY);
  return presentation->isRunning();
}

int UpOoPresentation::numSlidesInSlideshow()
{
  Reference<XPresentationSupplier> presentationSupplier(m_interface, UNO_QUERY);
  Reference<XPresentation2> presentation(presentationSupplier->getPresentation(),UNO_QUERY);
  Reference<XSlideShowController> controller = presentation->getController();
  return controller->getSlideCount();
}

int UpOoPresentation::currentSlideshowSlide()
{
  Reference<XPresentationSupplier> presentationSupplier(m_interface, UNO_QUERY);
  Reference<XPresentation2> presentation(presentationSupplier->getPresentation(),UNO_QUERY);
  Reference<XSlideShowController> controller = presentation->getController();
  return controller->getCurrentSlideIndex();
}

int UpOoPresentation::stepsInCurrentSlideshowSlide()
{
  return 1;
}

int UpOoPresentation::currentSlideshowStep()
{
  return 0;
}

/*
 * Slideshow control
 */

void UpOoPresentation::startSlideshow()
{
  Reference<XPresentationSupplier> presentationSupplier(m_interface, UNO_QUERY);
  Reference<XPresentation> presentation = presentationSupplier->getPresentation();
  presentation->start();
  emit slideshowStarted(numSlides());
  emit slideshowSlideChanged(0,1);
  emit slideshowStepChanged(0);
}

void UpOoPresentation::stopSlideshow()
{
  Reference<XPresentationSupplier> presentationSupplier(m_interface, UNO_QUERY);
  Reference<XPresentation> presentation = presentationSupplier->getPresentation();
  presentation->end();
  emit slideshowStopped();
}

void UpOoPresentation::goToSlide(int index)
{
  Reference<XPresentationSupplier> presentationSupplier(m_interface, UNO_QUERY);
  Reference<XPresentation2> presentation(presentationSupplier->getPresentation(),UNO_QUERY);
  Reference<XSlideShowController> controller = presentation->getController();
  controller->gotoSlideIndex(index);
  emit slideshowSlideChanged(controller->getCurrentSlideIndex(),1);
  emit slideshowStepChanged(0);
}

void UpOoPresentation::previousSlide()
{
  Reference<XPresentationSupplier> presentationSupplier(m_interface, UNO_QUERY);
  Reference<XPresentation2> presentation(presentationSupplier->getPresentation(),UNO_QUERY);
  Reference<XSlideShowController> controller = presentation->getController();
  controller->gotoPreviousSlide();
  emit slideshowSlideChanged(controller->getCurrentSlideIndex(),1);
  emit slideshowStepChanged(0);
}

void UpOoPresentation::nextSlide()
{
  Reference<XPresentationSupplier> presentationSupplier(m_interface, UNO_QUERY);
  Reference<XPresentation2> presentation(presentationSupplier->getPresentation(),UNO_QUERY);
  Reference<XSlideShowController> controller = presentation->getController();
  controller->gotoNextSlide();
  emit slideshowSlideChanged(controller->getCurrentSlideIndex(),1);
  emit slideshowStepChanged(0);
}

void UpOoPresentation::previousStep()
{
}

void UpOoPresentation::nextStep()
{
  Reference<XPresentationSupplier> presentationSupplier(m_interface, UNO_QUERY);
  Reference<XPresentation2> presentation(presentationSupplier->getPresentation(),UNO_QUERY);
  Reference<XSlideShowController> controller = presentation->getController();
  controller->gotoNextEffect();
  emit slideshowSlideChanged(controller->getCurrentSlideIndex(),1);
  emit slideshowStepChanged(0);
}

