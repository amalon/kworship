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

#ifndef _UpOkSlide_h_
#define _UpOkSlide_h_

/**
 * @file UpOkSlide.h
 * @brief Okular presentation slide.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpSlide.h"

class UpOkPresentation;

/// Okular presentation slide.
class UpOkSlide : public UpSlide
{
  Q_OBJECT
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpOkSlide(UpOkPresentation* presentation, int index);

    /// Destructor.
    virtual ~UpOkSlide();

    /*
     * Main interface
     */

    virtual QString title();
    virtual QString outline();
    virtual bool writeNotes(QTextDocument* doc);
    virtual QPixmap preview();

  private:

    /*
     * Variables
     */

    /// Presentation.
    UpOkPresentation* m_presentation;

    /// Slide index.
    int m_index;
};

#endif // _UpOkSlide_h_

