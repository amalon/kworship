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

#include <KLocale>
#include <KGenericFactory>

#include <QTimer>

K_EXPORT_COMPONENT_FACTORY( unipresent_kpresenter1, KGenericFactory<UpKpr1Backend>("unipresent_kpresenter1") )

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpKpr1Backend::UpKpr1Backend(QObject* parent, const QStringList& params)
: UpBackend(parent, params)
, m_presentations()
, m_refreshTimer(new QTimer(this))
{
  connect(m_refreshTimer, SIGNAL(timeout()), this, SLOT(refresh()));
  m_refreshTimer->start(15000);
  activate();
}

/// Destructor.
UpKpr1Backend::~UpKpr1Backend()
{
}

/*
 * General meta information
 */

QString UpKpr1Backend::id() const
{
  return "KOffice1/KPresenter";
}

QString UpKpr1Backend::UpKpr1Backend::name() const
{
  return i18n("KPresenter 1");
}

QString UpKpr1Backend::description() const
{
  return i18n("Controls a running KPresenter 1 presentation");
}

QStringList UpKpr1Backend::mimeTypes() const
{
  /// @todo Find mime types from kpresenter if possible
  return QStringList()
    << "application/x-kpresenter"
    << "application/vnd.oasis.opendocument.presentation"
    ;
}

QIcon UpKpr1Backend::icon() const
{
  return QIcon();
}

/*
 * Activation
 */

bool UpKpr1Backend::isActive()
{
  /// @todo Gently try again
  return !m_presentations.empty();
}

bool UpKpr1Backend::activate()
{
  refresh();
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

bool UpKpr1Backend::openPresentation(const QUrl& url)
{
  return false;
}

/*
 * Private slots
 */

/// Hit at intervals to refresh presentation list.
void UpKpr1Backend::refresh()
{
  QList<UpPresentation*> lostPresentations = m_presentations;

  UpKpr1AppsDcop apps;
  QList<UpKpr1KpresenterDcop> kprs = apps.kpresenters();
  foreach(UpKpr1KpresenterDcop kpr, kprs)
  {
    QList<UpKpr1PresentationDcop> docs = kpr.documents();
    foreach (UpKpr1PresentationDcop doc, docs)
    {
      // Must have a view to be useful
      UpKpr1ViewDcop view = doc.view();
      if (view.isValid())
      {
        UpPresentation* presentation = presentationByDcop(doc.reference());
        if (0 != presentation)
        {
          // Already exists, remove from lost list
          lostPresentations.removeOne(presentation);
        }
        else
        {
          // New, create
          presentation = new UpKpr1Presentation(doc, view, this);
          m_presentations << presentation;
          loadedPresentation(presentation);
        }
      }
    }
  }

  // Anything left in lost list needs removing
  foreach (UpPresentation* presentation, lostPresentations)
  {
    unloadedPresentation(presentation);
    delete presentation;
    m_presentations.removeOne(presentation);
  }
}

/*
 * Private functions
 */

/// Find a presentation identified by a dcop reference.
UpPresentation* UpKpr1Backend::presentationByDcop(const QStringList& dcopRef) const
{
  foreach (UpPresentation* presentation, m_presentations)
  {
    if (static_cast<UpKpr1Presentation*>(presentation)->dcop().reference() == dcopRef)
    {
      return presentation;
    }
  }
  return 0;
}
