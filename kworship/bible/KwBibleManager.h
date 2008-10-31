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

#ifndef _KwBibleManager_h_
#define _KwBibleManager_h_

/**
 * @file KwBibleManager.h
 * @brief A bible manager (analagous to a SWORD manager).
 * @author James Hogan <james@albanarts.com>
 */

#include <QString>
#include <QList>
#include <QMap>

class KwBibleModule;

namespace sword
{
  class SWMgr;
}

/// A bible manager (analagous to a SWORD manager).
class KwBibleManager
{
  public:

    /*
     * Singletonhood
     */

    /// Get the singleton object.
    static KwBibleManager* self();
    
    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwBibleManager();

    /// Destructor.
    virtual ~KwBibleManager();

    /*
     * Main interface
     */

    /// Get a module by name.
    KwBibleModule* module(const QString& name) const;

    /// Get the list of modules.
    QList<KwBibleModule*> modules() const;

  private:

    /*
     * Static variables
     */

    /// Singleton object.
    static KwBibleManager* s_self;

    /*
     * Variables
     */

    /// SWORD manager object.
    sword::SWMgr* m_manager;

    /// Modules managed by this manager.
    QMap<QString, KwBibleModule*> m_modules;
};

#endif // _KwBibleManager_h_

