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

#ifndef _UpKpr1Presentation_h_
#define _UpKpr1Presentation_h_

/**
 * @file UpKpr1Presentation.h
 * @brief KPresenter 1 presentation.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpKpr1PresentationDcop.h"
#include "UpPresentation.h"

/// KPresenter 1 presentation.
class UpKpr1Presentation : public UpPresentation
{
  Q_OBJECT
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpKpr1Presentation(const UpKpr1PresentationDcop& dcop, QObject* parent = 0);

    /// Destructor.
    virtual ~UpKpr1Presentation();

    /*
     * Main interface
     */

    virtual void close();

    virtual QUrl url() const;

    /*
     * Slides
     */

    virtual int numSlides();

    virtual UpSlide* slide(int index);

    /*
     * Slideshow control
     */

    virtual void startSlideshow();

    virtual void stopSlideshow();

    virtual void goToSlide(int index);

  private:

    /*
     * Variables
     */

    /// DCOP interface.
    UpKpr1PresentationDcop m_dcop;

    /// Url.
    QUrl m_url;
};

#endif // _UpKpr1Presentation_h_

