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

#ifndef _KwDisplayManager_h_
#define _KwDisplayManager_h_

/**
 * @file KwDisplayManager.h
 * @brief Display manager class.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwDisplayMixer.h"
#include "KwBackgroundManager.h"
#include "KwTextManager.h"
#include "KwOverlayManager.h"

class KwCssScope;

class KwMediaManager;

/// Abstract display management.
/**
 * High level interface for controlling a display object.
 */
class KwDisplayManager
{
  public:

    /*
     * Manager variables
     */

    /// Background manager.
    KwBackgroundManager background;

    /// Text manager.
    KwTextManager       text;

    /// Overlay manager.
    KwOverlayManager    overlay;

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwDisplayManager(KwAbstractDisplay* display, KwMediaManager* mediaManager);

    /// Destructor.
    virtual ~KwDisplayManager();

    /*
     * Main interface
     */

    /// Apply the styles in a scope.
    void applyStyles(KwCssScope* scope);

    /*
     * Accessors
     */

    /// Get the media manager.
    KwMediaManager* getMediaManager();

  private:

    /*
     * Variables
     */

    /// Display object.
    KwDisplayMixer m_mixer;

    /// Media manager.
    KwMediaManager* m_mediaManager;
};

#endif // _KwDisplayManager_h_

