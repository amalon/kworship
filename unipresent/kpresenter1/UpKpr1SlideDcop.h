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

#ifndef _UpKpr1SlideDcop_h_
#define _UpKpr1SlideDcop_h_

/**
 * @file UpKpr1SlideDcop.h
 * @brief DCOP interface for a kpresenter slide.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpKpr1Dcop.h"

/// DCOP interface for a kpresenter slide.
class UpKpr1SlideDcop : public UpKpr1Dcop
{
  public:

    /*
     * Constructors + destructor
     */

    /// Default constructor.
    UpKpr1SlideDcop();

    /// Primary constructor.
    UpKpr1SlideDcop(const UpKpr1Dcop& interface);

    /// Destructor.
    virtual ~UpKpr1SlideDcop();

    /*
     * Main interface
     */

    /// Get the title.
    QString title() const;

    /// Get the contents of the text objects in this slide.
    QStringList textObjectsContents() const;
};

#endif // _UpKpr1SlideDcop_h_

