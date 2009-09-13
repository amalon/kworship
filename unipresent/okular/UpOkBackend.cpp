/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008-2009 James Hogan <james@albanarts.com>                 *
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
 * @file UpOkBackend.cpp
 * @brief Okular presentation manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpOkBackend.h"
#include "UpOkProcess.h"
#include "UpOkPresentation.h"

#include <KRun>
#include <KLocale>
#include <KGenericFactory>
#include <KIcon>

#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDBusInterface>
#include <QStringList>

#include <cassert>

K_EXPORT_COMPONENT_FACTORY( unipresent_okular, KGenericFactory<UpOkBackend>("unipresent_okular") )

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpOkBackend::UpOkBackend(QObject* parent, const QStringList& params)
: UpBackend(parent, params)
, m_processes()
, m_presentations()
{
  QDBusConnectionInterface* interface = QDBusConnection::sessionBus().interface();
  connect(interface, SIGNAL(serviceOwnerChanged(const QString&, const QString&, const QString&)), this, SLOT(dbusServiceOwnerChange(const QString&, const QString&, const QString&)));

  QDBusReply<QStringList> reply = interface->registeredServiceNames();
  assert(reply.isValid());
  QStringList serviceNames = reply;
  foreach (QString serviceName, serviceNames)
  {
    if (serviceName.startsWith("org.kde.okular-"))
    {
      dbusServiceOwnerChange(serviceName, QString(), "dummy"); // the new owner string isn't used
    }
  }
}

/// Destructor.
UpOkBackend::~UpOkBackend()
{
  foreach (UpOkProcess* process, m_processes)
  {
    delete process;
  }
}

/*
 * General meta information
 */

QString UpOkBackend::id() const
{
  return "Okular";
}

QString UpOkBackend::name() const
{
  return i18n("Okular");
}

QString UpOkBackend::description() const
{
  return i18n("Controls a running Okular presentation");
}

QStringList UpOkBackend::mimeTypes() const
{
  /// @todo Find mime types from okular if possible
  return QStringList()
    << "application/pdf"
    ;
}

QIcon UpOkBackend::icon() const
{
  return KIcon("okular");
}

/*
 * Activation
 */

bool UpOkBackend::isActive()
{
  return !m_processes.isEmpty();
}

bool UpOkBackend::activate()
{
  return true;
}

void UpOkBackend::deactivate()
{
}

/*
 * Presentation management
 */

QList<UpPresentation*> UpOkBackend::presentations()
{
  return m_presentations;
}

bool UpOkBackend::openPresentation(const QUrl& url)
{
  // Ensure the program is up and running
  activate();

  // Check if the presentation is already open
  foreach (UpPresentation* presentation, m_presentations)
  {
    if (presentation->url() == url)
    {
      return true;
    }
  }

  // Otherwise open it now
  /// @todo Configurable okular exec
  bool started = KRun::run("okular", KUrl::List() << url, 0);

  return started;
}

/*
 * Private slots
 */

/// DBus service ownership change.
void UpOkBackend::dbusServiceOwnerChange(const QString& name, const QString& oldOwner, const QString& newOwner)
{
  // Is it an interesting service name?
  if (name.startsWith("org.kde.okular-"))
  {
    // Oooh, perhaps there are new presentations available
    if (oldOwner.isEmpty())
    {
      UpOkProcess* process = new UpOkProcess(name, this);
      m_processes[name] = process;
      // Link presentation event signals
      connect(process, SIGNAL(loadedPresentation(UpOkPresentation*)),
              this,    SLOT  (dbusLoadedPresentation(UpOkPresentation*)));
      connect(process, SIGNAL(unloadedPresentation(UpOkPresentation*)),
              this,    SLOT  (dbusUnloadedPresentation(UpOkPresentation*)));
      // Trigger adding of presentations that are already open
      QList<UpOkPresentation*> presentations = process->presentations();
      foreach (UpOkPresentation* pres, presentations)
      {
        dbusLoadedPresentation(pres);
      }
    }
    // Or perhaps the presentations are no longer available
    else if (newOwner.isEmpty())
    {
      QStringHashProcess::iterator it = m_processes.find(name);
      if (it != m_processes.end())
      {
        delete *it;
        m_processes.erase(it);
      }
    }
  }
}

// Slots for UpOkProcess signals

void UpOkBackend::dbusLoadedPresentation(UpOkPresentation* presentation)
{
  m_presentations.push_back(presentation);
  loadedPresentation(presentation);
}

void UpOkBackend::dbusUnloadedPresentation(UpOkPresentation* presentation)
{
  m_presentations.removeOne(presentation);
  unloadedPresentation(presentation);
}

