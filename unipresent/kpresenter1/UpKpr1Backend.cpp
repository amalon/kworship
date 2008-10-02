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
 * @file UpKpr1Backend.cpp
 * @brief KPresenter 1 presentation manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpKpr1Backend.h"
#include "UpKpr1AppsDcop.h"
#include "UpKpr1KpresenterDcop.h"
#include "UpKpr1PresentationDcop.h"
#include "UpKpr1Presentation.h"

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpKpr1Backend::UpKpr1Backend(QObject* parent)
: UpBackend(parent)
, m_presentations()
{
  activate();
}

/// Destructor.
UpKpr1Backend::~UpKpr1Backend()
{
}

/*
 * General meta information
 */

QString UpKpr1Backend::name() const
{
  return "KPresenter 1";
}

QString UpKpr1Backend::description() const
{
  return "Controls a running KPresenter 1 presentation";
}

QStringList UpKpr1Backend::mimeTypes() const
{
  /// @todo Find mime types from kpresenter if possible
  return QStringList()
    ;
}

QIcon UpKpr1Backend::icon() const
{
  return QIcon();
}

/*
 * Activation
 */

bool UpKpr1Backend::activate()
{
  if (m_presentations.empty())
  {
    UpKpr1AppsDcop apps;
    QList<UpKpr1KpresenterDcop> kprs = apps.kpresenters();
    foreach(UpKpr1KpresenterDcop kpr, kprs)
    {
      QList<UpKpr1PresentationDcop> docs = kpr.documents();
      foreach (UpKpr1PresentationDcop doc, docs)
      {
        m_presentations << new UpKpr1Presentation(doc, this);
      }
    }
  }
  return true;
}

void UpKpr1Backend::deactivate()
{
}

/*
 * Presentation management
 */

QList<UpPresentation*> UpKpr1Backend::presentations()
{
  return m_presentations;
}

UpPresentation* UpKpr1Backend::openPresentation(const QUrl& url)
{
  return 0;
}

