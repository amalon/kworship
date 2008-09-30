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

#ifndef _UpKpr1PresentationDcop_h_
#define _UpKpr1PresentationDcop_h_

/**
 * @file UpKpr1PresentationDcop.h
 * @brief DCOP interface for a kpresenter document.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpKpr1Dcop.h"
#include "UpKpr1SlideDcop.h"
#include "UpKpr1ViewDcop.h"

#include <QUrl>

/// DCOP interface for a kpresenter document.
class UpKpr1PresentationDcop : public UpKpr1Dcop
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpKpr1PresentationDcop(const UpKpr1Dcop& interface);

    /// Destructor.
    virtual ~UpKpr1PresentationDcop();

    /*
     * Main interface
     */

    /// Get the document url.
    QUrl url() const;

    /// Get the number of slides.
    int numPages() const;

    /// Get a particular slide by id.
    UpKpr1SlideDcop slide(int index) const;

    /// Get the view for this presentation.
    UpKpr1ViewDcop view(int index = 0) const;

  private:

    /*
     * Variables
     */

    /// Document id.
    int m_docId;

    /// Document url.
    QUrl m_url;
};

#endif // _UpKpr1PresentationDcop_h_

