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

#ifndef _UpKpr1Slide_h_
#define _UpKpr1Slide_h_

/**
 * @file UpKpr1Slide.h
 * @brief KPresenter 1 presentation slide.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpSlide.h"
#include "UpKpr1SlideDcop.h"

/// KPresenter 1 presentation slide.
class UpKpr1Slide : public UpSlide
{
  Q_OBJECT
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpKpr1Slide(const UpKpr1SlideDcop& dcop, QObject* parent = 0);

    /// Destructor.
    virtual ~UpKpr1Slide();

    /*
     * Main interface
     */

    virtual QString outline();

    virtual QString notes();

    virtual QPixmap preview();

  private:

    /*
     * Variables
     */

    /// DCOP interface.
    UpKpr1SlideDcop m_dcop;

    /// Outline text.
    QString m_outline;
};

#endif // _UpKpr1Slide_h_

