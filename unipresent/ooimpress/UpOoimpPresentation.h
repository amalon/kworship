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

#ifndef _UpOoimpPresentation_h_
#define _UpOoimpPresentation_h_

/**
 * @file UpOoimpPresentation.h
 * @brief OpenOffice.org Impress presentation.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpPresentation.h"

#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/uno/XInterface.hpp>

#include <QUrl>

using namespace com::sun::star;

/// OpenOffice.org Impress presentation.
class UpOoimpPresentation : public UpPresentation
{
  Q_OBJECT
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpOoimpPresentation(uno::XInterface* interface, QObject* parent = 0);

    /// Destructor.
    virtual ~UpOoimpPresentation();

    /*
     * Main interface
     */

    virtual void close();

    /*
     * Slides
     */

    virtual int numSlides();

    virtual UpSlide* getSlide(int);

  private:

    /*
     * Variables
     */

    /// An interface to the document.
    uno::Reference<uno::XInterface> m_interface;

    /// The file's URL.
    QUrl m_url;
};

#endif // _UpOoimpPresentation_h_

