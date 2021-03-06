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

/*
 * Manager factory
 */

/// Get a factory object.
KwBibleManager::Factory* KwBibleManager::factory()
{
  static Factory fac;
  return &fac;
}

/// Get a singleton for a manager.
KwBibleManager* KwBibleManager::singleton(const QString& key)
{
  return factory()->singleton(key);
}

/*
 * Constructors + destructor
 */

/// Default constructor.
KwBibleManager::KwBibleManager(QObject* parent, const QStringList& params)
: QObject(parent)
{
  Q_UNUSED(params);
}

/// Destructor.
KwBibleManager::~KwBibleManager()
{
}

