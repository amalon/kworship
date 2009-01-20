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

#include <KMimeType>
#include <KServiceTypeTrader>

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
, m_backendAssociations()
, m_preferredBackends()
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
    backendRemoved(backend);
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
bool UpManager::openPresentation(const QUrl& url, bool* attemptFailed)
{
  *attemptFailed = false;
  // This macro tries to open the url with the given backend
#define TRY_BACKEND_OPEN_PRESENTATION(BACKEND) \
  do \
  { \
    if (0 != (BACKEND)) \
    { \
      bool loaded = (BACKEND)->openPresentation(url); \
      if (loaded) \
      { \
        return true; \
      } \
      *attemptFailed = true; \
    } \
  } while (0)

  KSharedPtr<KMimeType> mimeType = KMimeType::findByUrl(url);

  // Check if this mime type has a specific association
  QStringHashString::const_iterator it = m_backendAssociations.constFind(mimeType->name());
  if (it != m_backendAssociations.constEnd())
  {
    UpBackend* backend = backendById(*it);
    TRY_BACKEND_OPEN_PRESENTATION(backend);
  }

  // Check if each preferred backend supports mime type
  foreach (QString backendId, m_preferredBackends)
  {
    UpBackend* backend = backendById(backendId);
    if (0 != backend)
    {
      QStringList supportedMimes = backend->mimeTypes();
      foreach (QString mime, supportedMimes)
      {
        if (mimeType->is(mime))
        {
          TRY_BACKEND_OPEN_PRESENTATION(backend);
        }
      }
    }
  }

  // Check all backends if they support mimetype
  foreach (UpBackend* backend, m_backends)
  {
    QStringList supportedMimes = backend->mimeTypes();
    foreach (QString mime, supportedMimes)
    {
      if (mimeType->is(mime))
      {
        TRY_BACKEND_OPEN_PRESENTATION(backend);
      }
    }
  }

  return false;

#undef TRY_BACKEND_OPEN_PRESENTATION
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
UpBackend* UpManager::backendByIndex(int index)
{
  return m_backends.at(index);
}

/// Get a specific backend by name.
UpBackend* UpManager::backendById(QString id)
{
  /// @todo This could be more efficient
  foreach (UpBackend* backend, m_backends)
  {
    if (backend->id() == id)
    {
      return backend;
    }
  }
  return 0;
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
  connect(backend, SIGNAL(loadedPresentation(UpPresentation*)), m_presentationsModel, SLOT(loadedPresentation(UpPresentation*)));
  connect(backend, SIGNAL(unloadedPresentation(UpPresentation*)), m_presentationsModel, SLOT(unloadedPresentation(UpPresentation*)));
  backendAdded(backend);
}

/// Load dynamic backend.
void UpManager::loadBackends()
{
  KService::List offers = KServiceTypeTrader::self()->query("UniPresent/Backend");

  foreach (KService::Ptr service, offers)
  {
    UpBackend* backend = service->createInstance<UpBackend>(this);
    if (backend)
    {
      addBackend(backend);
    }
  }
}
