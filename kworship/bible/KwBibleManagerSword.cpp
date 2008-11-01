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
 * @file KwBibleManagerSword.cpp
 * @brief A bible manager for SWORD.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBibleManagerSword.h"
#include "KwBibleModuleSword.h"

#include <swmgr.h>
#include <swmodule.h>
#include <markupfiltmgr.h>

/*
 * Constructors + destructor
 */

/// Default constructor.
KwBibleManagerSword::KwBibleManagerSword()
: KwBibleManager()
, m_manager(new sword::SWMgr(new sword::MarkupFilterMgr(sword::FMT_HTMLHREF)))
, m_modules()
{
  m_manager->setGlobalOption("Headings", "On");

  sword::ModMap::iterator modIterator;

  for (modIterator = m_manager->Modules.begin(); modIterator != m_manager->Modules.end(); ++modIterator)
  {
    sword::SWBuf modName = (*modIterator).first;
    sword::SWModule* module = (*modIterator).second;
    m_modules[QLatin1String(modName)] = new KwBibleModuleSword(module);
  }
}

/// Destructor.
KwBibleManagerSword::~KwBibleManagerSword()
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

QString KwBibleManagerSword::name() const
{
  return "SWORD";
}

bool KwBibleManagerSword::isRemote() const
{
  return false;
}

KwBibleModule* KwBibleManagerSword::module(const QString& name)
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

QStringList KwBibleManagerSword::moduleNames()
{
  return m_modules.keys();
}

QStringList KwBibleManagerSword::moduleNamesInLanguage(const QString& lang)
{
  return QStringList();
}

QStringList KwBibleManagerSword::languages()
{
  return QStringList();
}

