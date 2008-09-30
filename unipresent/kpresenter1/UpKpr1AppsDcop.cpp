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
 * @file UpKpr1AppsDcop.cpp
 * @brief DCOP interface for the list of applications.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpKpr1AppsDcop.h"
#include "UpKpr1KpresenterDcop.h"

/*
 * Constructors + destructor
 */

/// Default constructor.
UpKpr1AppsDcop::UpKpr1AppsDcop()
: UpKpr1Dcop(QStringList())
{
}

/// Destructor.
UpKpr1AppsDcop::~UpKpr1AppsDcop()
{
}

/*
 * Main interface
 */

/// Get an interface to kpresenter.
QList<UpKpr1KpresenterDcop> UpKpr1AppsDcop::kpresenters()
{
  bool error;
  QStringList apps = evalList(&error);
  QList<UpKpr1KpresenterDcop> results;
  if (!error)
  {
    foreach (QString app, apps)
    {
      if (app.startsWith("kpresenter-"))
      {
        results << UpKpr1KpresenterDcop(*this, app);
      }
    }
  }

  return results;
}

