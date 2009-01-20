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
 * @file UpKpr2Backend.cpp
 * @brief KPresenter 2 presentation manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpKpr2Backend.h"
#include "UpKpr2Process.h"
#include "UpKpr2Presentation.h"

#include <KRun>
#include <KLocale>
#include <KGenericFactory>

#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDBusInterface>
#include <QStringList>

#include <cassert>

K_EXPORT_COMPONENT_FACTORY( unipresent_kpresenter2, KGenericFactory<UpKpr2Backend>("unipresent_kpresenter2") )

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpKpr2Backend::UpKpr2Backend(QObject* parent, const QStringList& params)
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
    if (serviceName.startsWith("org.koffice.kpresenter-"))
    {
      dbusServiceOwnerChange(serviceName, QString(), "dummy"); // the new owner string isn't used
    }
  }
}

/// Destructor.
UpKpr2Backend::~UpKpr2Backend()
{
  foreach (UpKpr2Process* process, m_processes)
  {
    delete process;
  }
}

/*
 * General meta information
 */

QString UpKpr2Backend::id() const
{
  return "KOffice2/KPresenter";
}

QString UpKpr2Backend::name() const
{
  return i18n("KPresenter 2");
}

QString UpKpr2Backend::description() const
{
  return i18n("Controls a running KPresenter 2 presentation");
}

QStringList UpKpr2Backend::mimeTypes() const
{
  /// @todo Find mime types from kpresenter if possible
  return QStringList()
    << "application/x-kpresenter"
    << "application/vnd.oasis.opendocument.presentation"
    ;
}

QIcon UpKpr2Backend::icon() const
{
  return QIcon();
}

/*
 * Activation
 */

bool UpKpr2Backend::isActive()
{
  return !m_processes.isEmpty();
}

bool UpKpr2Backend::activate()
{
  return true;
}

void UpKpr2Backend::deactivate()
{
}

/*
 * Presentation management
 */

QList<UpPresentation*> UpKpr2Backend::presentations()
{
  return m_presentations;
}

bool UpKpr2Backend::openPresentation(const QUrl& url)
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
  /// @todo Configurable kpresenter exec
  bool started = KRun::run("kpresenter", KUrl::List() << url, 0);

  return started;
}

/*
 * Private slots
 */

/// DBus service ownership change.
void UpKpr2Backend::dbusServiceOwnerChange(const QString& name, const QString& oldOwner, const QString& newOwner)
{
  // Is it an interesting service name?
  if (name.startsWith("org.koffice.kpresenter-"))
  {
    // Oooh, perhaps there are new presentations available
    if (oldOwner.isEmpty())
    {
      UpKpr2Process* process = new UpKpr2Process(name, this);
      m_processes[name] = process;
      // Link presentation event signals
      connect(process, SIGNAL(loadedPresentation(UpKpr2Presentation*)),
              this,    SLOT  (dbusLoadedPresentation(UpKpr2Presentation*)));
      connect(process, SIGNAL(unloadedPresentation(UpKpr2Presentation*)),
              this,    SLOT  (dbusUnloadedPresentation(UpKpr2Presentation*)));
      // Trigger adding of presentations that are already open
      QList<UpKpr2Presentation*> presentations = process->presentations();
      foreach (UpKpr2Presentation* pres, presentations)
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

// Slots for UpKpr2Process signals

void UpKpr2Backend::dbusLoadedPresentation(UpKpr2Presentation* presentation)
{
  m_presentations.push_back(presentation);
  loadedPresentation(presentation);
}

void UpKpr2Backend::dbusUnloadedPresentation(UpKpr2Presentation* presentation)
{
  m_presentations.removeOne(presentation);
  unloadedPresentation(presentation);
}

