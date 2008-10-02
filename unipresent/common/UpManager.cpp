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
 * @file UpManager.cpp
 * @brief Overall unipresent manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpManager.h"
#include "UpManagerNode.h"
#include "UpBackend.h"
#include "UpPresentationsModel.h"

#include <cassert>

/// Singleton object.
UpManager* UpManager::s_singleton = 0;

/*
 * Singleton access.
 */

/// Get the singleton object.
UpManager* UpManager::self()
{
  return s_singleton;
}

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpManager::UpManager(QObject* parent)
: QObject(parent)
, m_backends()
, m_presentationsModel(new UpPresentationsModel(this))
{
  assert(s_singleton == 0);
  s_singleton = this;

  m_presentationsModel->setRootNode(new UpManagerNode(0, this));
}

/// Destructor.
UpManager::~UpManager()
{
  foreach(UpBackend* backend, m_backends)
  {
    delete backend;
  }
  s_singleton = 0;
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

/// Get a presentations model.
UpPresentationsModel* UpManager::presentationsModel()
{
  return m_presentationsModel;
}

/// Open a new presentation.
UpPresentation* UpManager::openPresentation(const QUrl& url)
{
  /// @todo Implement me properly
  foreach(UpBackend* backend, m_backends)
  {
    UpPresentation* pres = backend->openPresentation(url);
    if (0 != pres)
    {
      return pres;
    }
  }
  return 0;
}

/*
 * Backend management
 */

/// Get the number of backends.
int UpManager::numBackends() const
{
  return m_backends.size();
}

/// Get a specific backend.
UpBackend* UpManager::backend(int index)
{
  return m_backends.at(index);
}

/// Get a list of backends.
QList<UpBackend*> UpManager::backends()
{
  return m_backends;
}

/// Add a backend object.
void UpManager::addBackend(UpBackend* backend)
{
  m_backends.push_back(backend);
}

