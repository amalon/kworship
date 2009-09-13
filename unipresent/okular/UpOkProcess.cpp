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
 * @file UpOkProcess.cpp
 * @brief Okular process.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpOkProcess.h"
#include "UpOkPresentation.h"
#include "UpOkBackend.h"

#include "compiler.h"

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QStringList>

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpOkProcess::UpOkProcess(QString serviceName, UpOkBackend* parent)
: QObject(parent)
, m_backend(parent)
, m_serviceName(serviceName)
{
  // Get the current document
  QDBusInterface application(m_serviceName, "/okular", "org.kde.okular");
  if (application.isValid())
  {
    QString doc = application.call("currentDocument").arguments().first().toString();
    dbusPresentationOpened(doc);
  }
}

/// Destructor.
UpOkProcess::~UpOkProcess()
{
  foreach (UpOkPresentation* pres, m_presentations)
  {
    unloadedPresentation(pres);
    delete pres;
  }
}

/*
 * Basic accessors
 */

/// Get the service name.
QString UpOkProcess::serviceName() const
{
  return m_serviceName;
}

/// Get a list of presentations.
QList<UpOkPresentation*> UpOkProcess::presentations()
{
  return m_presentations.values();
}

/*
 * Private slots
 */

/// Indicates that a new presentation has been made available.
void UpOkProcess::dbusPresentationOpened(QString docName)
{
  Q_ASSERT(!docName.isEmpty());
  StringHashPresentation::iterator it = m_presentations.find(docName);
  if (likely(m_presentations.end() == it))
  {
    UpOkPresentation* pres = new UpOkPresentation(m_serviceName, m_backend, this);
    m_presentations[docName] = pres;
    loadedPresentation(pres);
  }
}

/// Indicates that an old presentation is no longer available.
void UpOkProcess::dbusPresentationClosed(QString docName)
{
  Q_ASSERT(!docName.isEmpty());
  StringHashPresentation::iterator it = m_presentations.find(docName);
  if (likely(m_presentations.end() != it))
  {
    UpOkPresentation* presentation = *it;
    m_presentations.erase(it);
    unloadedPresentation(presentation);
    delete presentation;
  }
}

