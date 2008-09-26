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

#ifndef _UpOoSlide_h_
#define _UpOoSlide_h_

/**
 * @file UpOoSlide.h
 * @brief OpenOffice.org presentation slide.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpSlide.h"

#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/uno/XInterface.hpp>

using namespace com::sun::star;

/// OpenOffice.org presentation slide.
class UpOoSlide : public UpSlide
{
  Q_OBJECT
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpOoSlide(uno::XInterface* interface, QObject* parent = 0);

    /// Destructor.
    virtual ~UpOoSlide();

    /*
     * Main interface
     */

    virtual QPixmap preview();

  private:

    /*
     * Variables
     */

    /// An interface to the document.
    uno::Reference<uno::XInterface> m_interface;

};

#endif // _UpOoSlide_h_

