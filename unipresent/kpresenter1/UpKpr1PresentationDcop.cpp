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
 * @file UpKpr1PresentationDcop.cpp
 * @brief DCOP interface for a kpresenter document.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpKpr1PresentationDcop.h"

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpKpr1PresentationDcop::UpKpr1PresentationDcop(const UpKpr1Dcop& interface)
: UpKpr1Dcop(interface)
{
}

/// Destructor.
UpKpr1PresentationDcop::~UpKpr1PresentationDcop()
{
}

/*
 * Main interface
 */

/// Get the document url.
QUrl UpKpr1PresentationDcop::url() const
{
  bool error;
  QStringList result = eval(&error, QStringList() << "url()");
  if (!error && result.size() == 1)
  {
    return QUrl(result.first());
  }
  else
  {
    return QUrl();
  }
}

/// Get the number of slides.
int UpKpr1PresentationDcop::numSlides() const
{
  bool error;
  QStringList result = eval(&error, QStringList() << "numPages()");
  if (!error && result.size() == 1)
  {
    bool ok;
    int numericResult = result.first().toInt(&ok);
    if (ok)
    {
      return numericResult;
    }
  }
  return 0;
}

/// Get a particular slide by id.
UpKpr1SlideDcop UpKpr1PresentationDcop::slide(int index)
{
  QString num;
  num.setNum(index);
  return evalRef(QStringList() << "page(int)" << num);
}

