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

#ifndef _UpKpr1AppsDcop_h_
#define _UpKpr1AppsDcop_h_

/**
 * @file UpKpr1AppsDcop.h
 * @brief DCOP interface for the list of applications.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpKpr1Dcop.h"

#include <QList>

class UpKpr1KpresenterDcop;

/// DCOP interface for the list of applications.
class UpKpr1AppsDcop : public UpKpr1Dcop
{
  public:

    /*
     * Constructors + destructor
     */

    /// Default constructor.
    UpKpr1AppsDcop();

    /// Destructor.
    virtual ~UpKpr1AppsDcop();

    /*
     * Main interface
     */

    /// Get an interface to kpresenter.
    QList<UpKpr1KpresenterDcop> kpresenters();
};

#endif // _UpKpr1AppsDcop_h_

