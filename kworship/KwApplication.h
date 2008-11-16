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

#ifndef _KwApplication_h_
#define _KwApplication_h_

/**
 * @file KwApplication.h
 * @brief Application global data.
 * @author James Hogan <james@albanarts.com>
 */

#include <KApplication>

class KwPluginManager;
class kworship;

/// Application global data.
class KwApplication
{
  public:

    /*
     * Singletonhood
     */

    /// Get the singleton application object.
    static KwApplication* self();

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwApplication();

    /// Destructor.
    virtual ~KwApplication();

    /*
     * Main interface
     */

    /// Execute the application.
    int exec();

    /*
     * Accessors
     */

    /// Get the main window widget.
    kworship* mainWindow();

    /// Get the plugin manager.
    KwPluginManager* pluginManager();

  private:

    /*
     * Static singleton data
     */

    /// Singleton application.
    static KwApplication* s_self;

    /*
     * Variables
     */

    /// KApplication object.
    KApplication m_app;

    /// Main window widget.
    kworship* m_mainWindow;

    /// Plugin manager.
    KwPluginManager* m_pluginManager;
};

#endif // _KwApplication_h_

