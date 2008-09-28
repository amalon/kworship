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
 * @file UpKpr1KpresenterDcop.cpp
 * @brief DCOP interface for a kpresenter process.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpKpr1KpresenterDcop.h"

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpKpr1KpresenterDcop::UpKpr1KpresenterDcop(const UpKpr1Dcop& parent, QString interface)
: UpKpr1Dcop(parent, interface)
{
}

/// Destructor.
UpKpr1KpresenterDcop::~UpKpr1KpresenterDcop()
{
}

/*
 * Main interface
 */

/// Get a list of documents.
QList<UpKpr1PresentationDcop> UpKpr1KpresenterDcop::documents() const
{
  bool error;
  QStringList docs = eval(error, QStringList() << "" << "getDocuments()");
  QList<UpKpr1PresentationDcop> results;
  if (!error)
  {
    foreach (QString doc, docs)
    {
      UpKpr1Dcop ref = dcopRefFromString(doc);
      if (ref.isValid())
      {
        results << UpKpr1PresentationDcop(ref);
      }
    }
  }

  return results;
}

