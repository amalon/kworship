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
 * @file KwBibleManagerBibleGateway.cpp
 * @brief A bible manager for BibleGateway.com.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBibleManagerBibleGateway.h"
#include "KwBibleModuleBibleGateway.h"

/*
 * Constructors + destructor
 */

/// Default constructor.
KwBibleManagerBibleGateway::KwBibleManagerBibleGateway()
: KwBibleManager()
, m_moduleNames()
, m_modules()
{
}

/// Destructor.
KwBibleManagerBibleGateway::~KwBibleManagerBibleGateway()
{
  foreach (KwBibleModule* module, m_modules)
  {
    delete module;
  }
}

/*
 * Main interface
 */

QString KwBibleManagerBibleGateway::name() const
{
  return "BibleGateway.com";
}

bool KwBibleManagerBibleGateway::isRemote() const
{
  return true;
}

KwBibleModule* KwBibleManagerBibleGateway::module(const QString& name)
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

QStringList KwBibleManagerBibleGateway::moduleNames()
{
  // Connect now
  
  return m_moduleNames;
}

QStringList KwBibleManagerBibleGateway::moduleNamesInLanguage(const QString& lang)
{
  return QStringList();
}

QStringList KwBibleManagerBibleGateway::languages()
{
  return QStringList();
}

