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

#ifndef _UpKpr1KpresenterDcop_h_
#define _UpKpr1KpresenterDcop_h_

/**
 * @file UpKpr1KpresenterDcop.h
 * @brief DCOP interface for a kpresenter process.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpKpr1Dcop.h"
#include "UpKpr1PresentationDcop.h"

/// DCOP interface for a kpresenter process.
class UpKpr1KpresenterDcop : public UpKpr1Dcop
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpKpr1KpresenterDcop(const UpKpr1Dcop& parent, QString interface);

    /// Destructor.
    virtual ~UpKpr1KpresenterDcop();

    /*
     * Main interface
     */

    /// Get a list of documents.
    QList<UpKpr1PresentationDcop> documents() const;
};

#endif // _UpKpr1KpresenterDcop_h_

