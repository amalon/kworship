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
 * @file KwPlugin.cpp
 * @brief An abstract KWorship plugin.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlugin.h"
#include "KwPluginManager.h"

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwPlugin::KwPlugin(QObject* parent, const QString& id, const QString& name, const QString& description)
: KParts::Plugin(parent)
, m_id(id)
, m_name(name)
, m_description(description)
, m_manager(0)
, m_loaded(false)
{
}

/// Destructor.
KwPlugin::~KwPlugin()
{
}

/*
 * Basic information accessors
 */

/// Get the id.
const QString& KwPlugin::id() const
{
  return m_id;
}

/// Get the name.
const QString& KwPlugin::name() const
{
  return m_name;
}

/// Get the description.
const QString& KwPlugin::description() const
{
  return m_description;
}

/// Get whether the plugin is loaded.
bool KwPlugin::isLoaded() const
{
  return m_loaded;
}

/*
 * Loading and unloading
 */

/// Set the manager.
void KwPlugin::setManager(KwPluginManager* manager)
{
  Q_ASSERT(0 == m_manager);
  m_manager = manager;
}

/// Load the plugin.
void KwPlugin::load()
{
  if (!m_loaded)
  {
    _load();
  }
}

/// Unload the plugin.
void KwPlugin::unload()
{
  if (m_loaded)
  {
    _unload();
  }
}

