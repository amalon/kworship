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

#ifndef _UpKpr2Slide_h_
#define _UpKpr2Slide_h_

/**
 * @file UpKpr2Slide.h
 * @brief KPresenter 2 presentation slide.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpSlide.h"

class UpKpr2Presentation;

/// KPresenter 2 presentation slide.
class UpKpr2Slide : public UpSlide
{
  Q_OBJECT
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpKpr2Slide(UpKpr2Presentation* presentation, int index);

    /// Destructor.
    virtual ~UpKpr2Slide();

    /*
     * Main interface
     */

    virtual QString title();
    virtual QString outline();
    virtual QString notes();
    virtual QPixmap preview();

  private:

    /*
     * Variables
     */

    /// Presentation.
    UpKpr2Presentation* m_presentation; 

    /// Slide index.
    int m_index;

    /// Title text.
    QString m_title;

    /// Outline text.
    QString m_outline;

    /// Preview pixmap.
    QPixmap m_preview;
};

#endif // _UpKpr2Slide_h_

