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

#ifndef _KwResourceManager_h_
#define _KwResourceManager_h_

/**
 * @file KwResourceManager.h
 * @brief Manages external resources when loading/saving data files.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwResourceLink.h"

/** Manages external resources when loading/saving data files.
 * This abstract base class defines an interface which can be used to ensure
 * that any resource files that are required when constructing a data archive
 * can be safely linked to.
 */
class KwResourceManager
{
  public:

    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwResourceManager();

    /// Destructor.
    virtual ~KwResourceManager();

    /*
     * Main resource interface
     */

    /// Add a resource to the manager.
    virtual void addResource(const KwResourceLink* link) = 0;

};

#endif // _KwResourceManager_h_

