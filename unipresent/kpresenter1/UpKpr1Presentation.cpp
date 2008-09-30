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

#include <cassert>

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpKpr1Presentation::UpKpr1Presentation(const UpKpr1PresentationDcop& dcop, QObject* parent)
: UpPresentation(parent)
, m_dcop(dcop)
, m_dcopView(dcop.view())
, m_url(dcop.url())
{
  assert(m_dcopView.isValid());
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
  return m_dcop.numPages();
}

UpSlide* UpKpr1Presentation::slide(int index)
{
  return new UpKpr1Slide(this, m_dcop.slide(index), index);
}

/*
 * Slideshow control
 */

void UpKpr1Presentation::startSlideshow()
{
  m_dcopView.screenStartFromFirst();
}

void UpKpr1Presentation::stopSlideshow()
{
  m_dcopView.screenStop();
}

void UpKpr1Presentation::goToSlide(int index)
{
  m_dcopView.gotoPresPage(index+1);
}

void UpKpr1Presentation::previousSlide()
{
  int newPage = m_dcopView.getCurrentPresPage() - 1;
  if (newPage > 0)
  {
    m_dcopView.gotoPresPage(newPage);
  }
}

void UpKpr1Presentation::nextSlide()
{
  int presPages = m_dcopView.getNumPresPages();
  int newPage = m_dcopView.getCurrentPresPage() + 1;
  if (newPage <= presPages)
  {
    m_dcopView.gotoPresPage(newPage);
  }
}

void UpKpr1Presentation::previousStep()
{
  m_dcopView.screenPrev();
}

void UpKpr1Presentation::nextStep()
{
  // don't go past the end of the slideshow
  bool operate = true;
  int steps = m_dcopView.getPresStepsOfPage();
  int step = m_dcopView.getCurrentPresStep();
  if (step == steps - 1)
  {
    int pages = m_dcopView.getNumPresPages();
    int page = m_dcopView.getCurrentPresPage();
    if (page == pages)
    {
      operate = false;
    }
  }
  if (operate)
  {
    m_dcopView.screenNext();
  }
}

/*
 * Backend specific interface.
 */

/// Get the dcop interface.
UpKpr1PresentationDcop UpKpr1Presentation::dcop() const
{
  return m_dcop;
}

/// Get the dcop view interface.
UpKpr1ViewDcop UpKpr1Presentation::dcopView() const
{
  return m_dcopView;
}

#include "UpKpr1Presentation.moc"

