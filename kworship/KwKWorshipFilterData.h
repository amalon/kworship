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

#ifndef _KwKWorshipFilterData_h_
#define _KwKWorshipFilterData_h_

/**
 * @file KwKWorshipFilterData.h
 * @brief Additional KWorship import data.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwFilterData.h"

#include <QDomDocumentFragment>
#include <QString>

/// Additional KWorship import data.
class KwKWorshipFilterData : public KwFilterData
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwKWorshipFilterData();

    /// Destructor.
    virtual ~KwKWorshipFilterData();

    /*
     * Import filter interface
     */

    /** Indicate that elements of a particular tag name have been handled.
     * This clears the specified elements from the DOM preserve.
     */
    void elementsHandled(const QString& tagName);

    /** Indicate that the first elements of a particular tag name have been handled.
     * This clears the specified element from the DOM preserve.
     */
    void elementHandled(const QString& tagName);

  private:

    /*
     * Variables
     */

    /// Document to store fragment in.
    QDomDocument m_domDocument;

    /// Fragment of DOM from save file which needs preserving.
    QDomDocumentFragment m_domPreserve;
};

#endif // _KwKWorshipFilterData_h_
