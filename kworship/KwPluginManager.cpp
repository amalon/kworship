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
#include <KXmlGuiWindow>
#include <KXMLGUIFactory>

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwPluginManager::KwPluginManager()
: m_plugins()
, m_mainWindow(0)
{
}

/// Destructor.
KwPluginManager::~KwPluginManager()
{
  foreach (KwPlugin* plugin, m_plugins)
  {
    plugin->unload();
    delete plugin;
  }
}

/*
 * Plugin loading and unloading
 */

/// Set the main window.
void KwPluginManager::setMainWindow(KXmlGuiWindow* mainWindow)
{
  m_mainWindow = mainWindow;
}

/// Directly load a plugin.
bool KwPluginManager::loadPlugin(KwPlugin* plugin)
{
  const QString& id = plugin->id();
  Q_ASSERT(!plugin->isLoaded());
  if (!m_plugins.contains(id))
  {
    m_plugins[id] = plugin;
    if (m_mainWindow)
    {
      m_mainWindow->guiFactory()->addClient(plugin);
    }
    plugin->load();
    return true;
  }
  return false;
}

#include <QtDebug>
/// Load all plugins.
void KwPluginManager::loadPlugins()
{
  KService::List offers = KServiceTypeTrader::self()->query("KWorship/Plugin");

  foreach (KService::Ptr service, offers)
  {
    qDebug() << "Found KWorship plugin: " << service->desktopEntryName();
    QString err;
    KwPlugin* plugin = service->createInstance<KwPlugin>(this, QVariantList(), &err);
    if (plugin)
    {
      bool loaded = loadPlugin(plugin);
      if (loaded)
      {
        qDebug() << "  Loaded successfully";
      }
      else
      {
        qDebug() << "  Could not be initialised";
      }
    }
    else
    {
      qDebug() << "  Could not be loaded: " << err;
    }
  }
}

