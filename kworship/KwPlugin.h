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

#ifndef _KwPlugin_h_
#define _KwPlugin_h_

/**
 * @file KwPlugin.h
 * @brief An abstract KWorship plugin.
 * @author James Hogan <james@albanarts.com>
 */

#include <QObject>
#include <QString>

class KwPluginManager;

class QMainWindow;
class QDockWidget;

/// An abstract KWorship plugin.
class KwPlugin : public QObject
{
    Q_OBJECT

  public:

    /*
     * Constructors + destructor
     */

    /** Primary constructor.
     * @param id Short unique untranslated id.
     * @param name Translated name of plugin.
     * @param description Translated description of plugin.
     */
    KwPlugin(const QString& id, const QString& name, const QString& description);

    /// Destructor.
    virtual ~KwPlugin();

    /*
     * Basic information accessors
     */

    /// Get the id.
    const QString& id() const;

    /// Get the name.
    const QString& name() const;

    /// Get the description.
    const QString& description() const;

    /// Get whether the plugin is loaded.
    bool isLoaded() const;

    /*
     * Loading and unloading
     */

    /** Set the manager.
     * This should only be called by the manager class itself.
     * @pre Manager must not have already been set.
     * @param manager New manager object.
     */
    void setManager(KwPluginManager* manager);

    /** Load the plugin.
     * @pre Manager must have been set.
     */
    void load(QMainWindow* mainWindow);

    /// Unload the plugin.
    void unload();

  protected:

    /*
     * Loading and unloading virtual interface
     */

    /** Load the plugin.
     * @pre !isLoaded()
     */
    virtual void _load(QMainWindow* mainWindow) = 0;

    /** Unload the plugin.
     * @pre isLoaded()
     */
    virtual void _unload() = 0;

  private:

    /*
     * Constants
     */

    /// Short unique untranslated id.
    QString m_id;

    /// Translated name.
    QString m_name;

    /// Translated description.
    QString m_description;

    /*
     * Variables
     */

    /// The current plugin manager.
    KwPluginManager* m_manager;

    /// Whether the plugin is loaded.
    bool m_loaded;

};

#endif // _KwPlugin_h_

