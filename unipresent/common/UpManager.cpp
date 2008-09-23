/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   KWorship is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   KWorship is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with KWorship.  If not, see <http://www.gnu.org/licenses/>.     *
 ***************************************************************************/

/**
 * @file UpManager.cpp
 * @brief Overall unipresent manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpManager.h"
#include "UpBackend.h"

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpManager::UpManager(QObject* parent)
: QObject(parent)
, m_backends()
{
}

/// Destructor.
UpManager::~UpManager()
{
  foreach(UpBackend* backend, m_backends)
  {
    delete backend;
  }
}

/*
 * Presentation management
 */

/// Get a list of presentations.
QList<UpPresentation*> UpManager::presentations()
{
  QList<UpPresentation*> presentations;
  foreach(UpBackend* backend, m_backends)
  {
    presentations << backend->presentations();
  }
  return presentations;
}

/// Open a new presentation.
UpPresentation* UpManager::openPresentation(const QUrl& url)
{
  /// Implement me
  return 0;
}

/*
 * Backend management
 */

/// Get a list of backends.
QList<UpBackend*> UpManager::backends()
{
  return m_backends;
}

