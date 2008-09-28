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
 * @file UpKpr1Presentation.cpp
 * @brief KPresenter 1 presentation.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpKpr1Presentation.h"
#include "UpKpr1Slide.h"

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpKpr1Presentation::UpKpr1Presentation(const UpKpr1PresentationDcop& dcop, QObject* parent)
: UpPresentation(parent)
, m_dcop(dcop)
, m_url(dcop.url())
{
}

/// Destructor.
UpKpr1Presentation::~UpKpr1Presentation()
{
}

/*
 * Main interface
 */

void UpKpr1Presentation::close()
{
}

QUrl UpKpr1Presentation::url() const
{
  return m_url;
}

/*
 * Slides
 */

int UpKpr1Presentation::numSlides()
{
  return m_dcop.numSlides();
}

UpSlide* UpKpr1Presentation::slide(int index)
{
  return new UpKpr1Slide(m_dcop.slide(index), this);
}

/*
 * Slideshow control
 */

void UpKpr1Presentation::startSlideshow()
{
}

void UpKpr1Presentation::stopSlideshow()
{
}

#include "UpKpr1Presentation.moc"

