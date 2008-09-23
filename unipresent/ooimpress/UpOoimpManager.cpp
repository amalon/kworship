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
 * @file UpOoimpManager.cpp
 * @brief OpenOffice.org Impress presentation manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpOoimpManager.h"

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpOoimpManager::UpOoimpManager(QObject* parent)
: UpManager(parent)
{
}

/// Destructor.
UpOoimpManager::~UpOoimpManager()
{
}

/*
 * General meta information
 */

QString UpOoimpManager::name() const
{
  return "OpenOffice.org Impress";
}

QString UpOoimpManager::description() const
{
  return "Controls a running Impress";
}

QStringList UpOoimpManager::mimeTypes() const
{
  /// @todo Find mime types from open office if possible
  return QStringList()
    << "application/vnd.oasis.opendocument.presentation"
    ;
}

/*
 * Presentation management
 */

QList<UpPresentation*> UpOoimpManager::presentations()
{
  return QList<UpPresentation*>();
}

UpPresentation* UpOoimpManager::openPresentation(const QUrl& url)
{
  return 0;
}

