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

#ifndef _KwPluginManager_h_
#define _KwPluginManager_h_

/**
 * @file KwPluginManager.h
 * @brief Manages KWorship plugins.
 * @author James Hogan <james@albanarts.com>
 */

#include <QObject>
#include <QMap>
#include <QString>

class KwPlugin;

/** Manages KWorship plugins.
 * @todo Dynamic loading/unloading of plugins.
 */
class KwPluginManager : public QObject
{
    Q_OBJECT

  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwPluginManager();

    /// Destructor.
    virtual ~KwPluginManager();

    /*
     * Plugin loading and unloading
     */

    /** Directly load a plugin.
     * @param plugin The plugin object.
     * @returns True on success, false otherwise.
     */
    bool loadPlugin(KwPlugin* plugin);

    /// Load all plugins.
    void loadPlugins();

  private:

    /*
     * Variables
     */

    /// Plugins by id.
    QMap<QString, KwPlugin*> m_plugins;
};

#endif // _KwPluginManager_h_

