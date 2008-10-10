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
 * @file UpKpr2Process.cpp
 * @brief KPresenter 2 process.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpKpr2Process.h"
#include "UpKpr2Presentation.h"
#include "UpKpr2Backend.h"

#include "compiler.h"

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QStringList>

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpKpr2Process::UpKpr2Process(QString serviceName, UpKpr2Backend* parent)
: QObject(parent)
, m_backend(parent)
, m_serviceName(serviceName)
{
  // Set up document event signals so we know when to create/remove documents
  QDBusConnection::sessionBus().connect(serviceName, "/application", "org.kde.koffice.application", "documentOpened", this, SLOT(dbusPresentationOpened(QString)));
  QDBusConnection::sessionBus().connect(serviceName, "/application", "org.kde.koffice.application", "documentClosed", this, SLOT(dbusPresentationClosed(QString)));

  // Get the current list of documents
  QDBusInterface application(m_serviceName, "/application", "org.kde.koffice.application");
  if (application.isValid())
  {
    QStringList docs = application.call("getDocuments").arguments().first().toStringList();
    foreach (QString doc, docs)
    {
      QDBusInterface application(m_serviceName, doc, "org.kde.koffice.document");
      int views = (QDBusReply<int>)application.call("viewCount");
      if (views > 0)
      {
        dbusPresentationOpened(doc);
      }
    }
  }
}

/// Destructor.
UpKpr2Process::~UpKpr2Process()
{
  foreach (UpKpr2Presentation* pres, m_presentations)
  {
    unloadedPresentation(pres);
    delete pres;
  }
}

/*
 * Basic accessors
 */

/// Get the service name.
QString UpKpr2Process::serviceName() const
{
  return m_serviceName;
}

/// Get a list of presentations.
QList<UpKpr2Presentation*> UpKpr2Process::presentations()
{
  return m_presentations.values();
}

/*
 * Private slots
 */

/// Indicates that a new presentation has been made available.
void UpKpr2Process::dbusPresentationOpened(QString docName)
{
  Q_ASSERT(!docName.isEmpty());
  StringHashPresentation::iterator it = m_presentations.find(docName);
  if (likely(m_presentations.end() == it))
  {
    UpKpr2Presentation* pres = new UpKpr2Presentation(m_serviceName, docName, m_backend, this);
    m_presentations[docName] = pres;
    loadedPresentation(pres);
  }
}

/// Indicates that an old presentation is no longer available.
void UpKpr2Process::dbusPresentationClosed(QString docName)
{
  Q_ASSERT(!docName.isEmpty());
  StringHashPresentation::iterator it = m_presentations.find(docName);
  if (likely(m_presentations.end() != it))
  {
    UpKpr2Presentation* presentation = *it;
    m_presentations.erase(it);
    unloadedPresentation(presentation);
    delete presentation;
  }
}

