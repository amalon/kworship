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

/**
 * @file KwPluginManager.cpp
 * @brief Manages KWorship plugins.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPluginManager.h"
#include "KwPlugin.h"

#include <KServiceTypeTrader>

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwPluginManager::KwPluginManager()
: m_plugins()
{
}

/// Destructor.
KwPluginManager::~KwPluginManager()
{
}

/*
 * Plugin loading and unloading
 */

/// Directly load a plugin.
bool KwPluginManager::loadPlugin(KwPlugin* plugin)
{
  const QString& id = plugin->id();
  Q_ASSERT(!plugin->isLoaded());
  if (!m_plugins.contains(id))
  {
    m_plugins[id] = plugin;
    plugin->load();
    return true;
  }
  return false;
}

/// Load all plugins.
void KwPluginManager::loadPlugins()
{
  KService::List offers = KServiceTypeTrader::self()->query("KWorship/Plugin");

  foreach (KService::Ptr service, offers)
  {
    KwPlugin* plugin = service->createInstance<KwPlugin>(this);
    if (plugin)
    {
      loadPlugin(plugin);
    }
  }
}

