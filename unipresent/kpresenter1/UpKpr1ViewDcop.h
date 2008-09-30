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

#ifndef _UpKpr1ViewDcop_h_
#define _UpKpr1ViewDcop_h_

/**
 * @file UpKpr1ViewDcop.h
 * @brief DCOP interface for a kpresenter document view.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpKpr1Dcop.h"

/// DCOP interface for a kpresenter document view.
class UpKpr1ViewDcop : public UpKpr1Dcop
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpKpr1ViewDcop(const UpKpr1Dcop& interface);

    /// Destructor.
    virtual ~UpKpr1ViewDcop();

    /*
     * Main interface
     */

    void screenStart() const;
    void screenStartFromFirst() const;
    void screenStop() const;
    void screenPause() const;
    void screenFirst() const;
    void screenPrev() const;
    void screenNext() const;
    void screenLast() const;
    void screenSkip() const;
    int getCurrentPresPage() const;
    int getCurrentPresStep() const;
    int getPresStepsOfPage() const;
    int getNumPresPages() const;
    void gotoPresPage(int pg) const;
};

#endif // _UpKpr1ViewDcop_h_

