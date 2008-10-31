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
 * @file KwBibleManager.cpp
 * @brief A bible manager (analagous to a SWORD manager).
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBibleManager.h"
#include "KwBibleModule.h"

#include <swmgr.h>
#include <swmodule.h>
#include <markupfiltmgr.h>

/*
 * Static variables
 */

/// Singleton object.
KwBibleManager* KwBibleManager::s_self = 0;

/*
 * Singletonhood
 */

/// Get the singleton object.
KwBibleManager* KwBibleManager::self()
{
  if (0 == s_self)
  {
    s_self = new KwBibleManager;
  }
  return s_self;
}

/*
 * Constructors + destructor
 */

/// Default constructor.
KwBibleManager::KwBibleManager()
: m_manager(new sword::SWMgr(new sword::MarkupFilterMgr(sword::FMT_HTMLHREF)))
, m_modules()
{
  sword::ModMap::iterator modIterator;

  for (modIterator = m_manager->Modules.begin(); modIterator != m_manager->Modules.end(); ++modIterator)
  {
    sword::SWBuf modName = (*modIterator).first;
    sword::SWModule* module = (*modIterator).second;
    m_modules[QLatin1String(modName)] = new KwBibleModule(module);
  }
}

/// Destructor.
KwBibleManager::~KwBibleManager()
{
  foreach (KwBibleModule* module, m_modules)
  {
    delete module;
  }
  delete m_manager;
}

/*
 * Main interface
 */

/// Get a module by name.
KwBibleModule* KwBibleManager::module(const QString& name) const
{
  QMap<QString, KwBibleModule*>::const_iterator it = m_modules.constFind(name);
  if (it != m_modules.constEnd())
  {
    return *it;
  }
  else
  {
    return 0;
  }
}

/// Get the list of modules.
QList<KwBibleModule*> KwBibleManager::modules() const
{
  return m_modules.values();

}

