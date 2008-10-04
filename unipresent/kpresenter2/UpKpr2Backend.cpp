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

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpKpr2Backend::UpKpr2Backend(QObject* parent)
: UpBackend(parent)
, m_presentations()
{
  activate();
}

/// Destructor.
UpKpr2Backend::~UpKpr2Backend()
{
}

/*
 * General meta information
 */

QString UpKpr2Backend::name() const
{
  return "KPresenter 2";
}

QString UpKpr2Backend::description() const
{
  return "Controls a running KPresenter 2 presentation";
}

QStringList UpKpr2Backend::mimeTypes() const
{
  /// @todo Find mime types from kpresenter if possible
  return QStringList()
    ;
}

QIcon UpKpr2Backend::icon() const
{
  return QIcon();
}

/*
 * Activation
 */

bool UpKpr2Backend::activate()
{
  if (m_presentations.empty())
  {
    
  }
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

UpPresentation* UpKpr2Backend::openPresentation(const QUrl& url)
{
  return 0;
}

