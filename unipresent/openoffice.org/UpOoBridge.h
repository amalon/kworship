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

#ifndef _UpOoBridge_h_
#define _UpOoBridge_h_

/**
 * @file UpOoBridge.h
 * @brief Bridge to OpenOffice.org.
 * @author James Hogan <james@albanarts.com>
 */

#include <com/sun/star/uno/XInterface.hpp>

// lets make it a little easier for us without cluttering namespace
using namespace com::sun::star;

/// Bridge to OpenOffice.org.
class UpOoBridge
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpOoBridge();

    /// Destructor.
    virtual ~UpOoBridge();

    /*
     * Main interface
     */

    /// Find whether the bridge is valid.
    bool isValid() const;

    /// Get the service manager.
    uno::XInterface* serviceManager();

  private:

    /*
     * Variables
     */

    /// Whether the bridge is valid.
    bool m_valid;

    /// Service manager interface.
    uno::Reference<uno::XInterface> m_serviceManager;
};

#endif // _UpOoBridge_h_

