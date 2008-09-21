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

#ifndef _KwAbstractDisplayManager_h_
#define _KwAbstractDisplayManager_h_

/**
 * @file KwAbstractDisplayManager.h
 * @brief Abstract display manager class.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwLocalDisplayController.h"

class KwDisplayMixer;

/// Abstract display manager class.
/**
 * High level interface for controlling a display object.
 */
class KwAbstractDisplayManager
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwAbstractDisplayManager();

    /// Destructor.
    virtual ~KwAbstractDisplayManager();

    /*
     * Main interface
     */

    /// Attach the display to the top of a mixer.
    void attachToMixer(KwDisplayMixer* mixer);

  protected:

    /*
     * Variables
     */

    /// Display object.
    KwLocalDisplayController m_display;
};

#endif // _KwAbstractDisplayManager_h_

