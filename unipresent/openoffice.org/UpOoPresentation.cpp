/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   KWorship is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   KWorship is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with KWorship.  If not, see <http://www.gnu.org/licenses/>.     *
 ***************************************************************************/

/**
 * @file UpOoPresentation.cpp
 * @brief OpenOffice.org presentation.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpOoPresentation.h"
#include "UpOoSlide.h"

#include <com/sun/star/container/XIndexAccess.hpp>
#include <com/sun/star/drawing/XDrawPagesSupplier.hpp>
#include <com/sun/star/drawing/XDrawPages.hpp>
#include <com/sun/star/drawing/XDrawPage.hpp>
#include <com/sun/star/frame/XModel.hpp>
#include <com/sun/star/presentation/XPresentationSupplier.hpp>
#include <com/sun/star/presentation/XPresentation.hpp>

#include <cassert>

using namespace com::sun::star::drawing;
using namespace com::sun::star::frame;
using namespace com::sun::star::presentation;
using namespace com::sun::star::uno;

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpOoPresentation::UpOoPresentation(uno::XInterface* interface, QObject* parent)
: UpPresentation(parent)
, m_interface(interface)
, m_url()
{
  // Get the url
  Reference<XModel> model(interface, UNO_QUERY);
  assert(0 != model.get());
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
 * Slides
 */

int UpOoPresentation::numSlides()
{
  Reference<XDrawPagesSupplier> drawPagesSupplier(m_interface, UNO_QUERY);
  assert(0 != drawPagesSupplier.get());
  Reference<XDrawPages> drawPages = drawPagesSupplier->getDrawPages();
  return drawPages->getCount();
}

UpSlide* UpOoPresentation::slide(int index)
{
  Reference<XDrawPagesSupplier> drawPagesSupplier(m_interface, UNO_QUERY);
  assert(0 != drawPagesSupplier.get());
  Reference<XDrawPages> drawPages = drawPagesSupplier->getDrawPages();
  Reference<XDrawPage> drawPage;
  drawPages->getByIndex(index) >>= drawPage;
  return new UpOoSlide(drawPage.get(), this);
}

/*
 * Slideshow control
 */

void UpOoPresentation::startSlideshow()
{
  Reference<XPresentationSupplier> presentationSupplier(m_interface, UNO_QUERY);
  Reference<XPresentation> presentation = presentationSupplier->getPresentation();
  presentation->start();
}

void UpOoPresentation::stopSlideshow()
{
  Reference<XPresentationSupplier> presentationSupplier(m_interface, UNO_QUERY);
  Reference<XPresentation> presentation = presentationSupplier->getPresentation();
  presentation->end();
}

void UpOoPresentation::goToSlide(int index)
{
}

#include "UpOoPresentation.moc"

