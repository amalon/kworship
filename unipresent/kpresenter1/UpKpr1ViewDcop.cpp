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
 * @file UpKpr1ViewDcop.cpp
 * @brief DCOP interface for a kpresenter document view.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpKpr1ViewDcop.h"

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpKpr1ViewDcop::UpKpr1ViewDcop(const UpKpr1Dcop& interface)
: UpKpr1Dcop(interface)
{
}

/// Destructor.
UpKpr1ViewDcop::~UpKpr1ViewDcop()
{
}

/*
 * Main interface
 */

void UpKpr1ViewDcop::screenStart() const
{
  eval(QStringList() << "screenStart()");
}

void UpKpr1ViewDcop::screenStartFromFirst() const
{
  eval(QStringList() << "screenStartFromFirst()");
}

void UpKpr1ViewDcop::screenStop() const
{
  eval(QStringList() << "screenStop()");
}

void UpKpr1ViewDcop::screenPause() const
{
  eval(QStringList() << "screenPause()");
}

void UpKpr1ViewDcop::screenFirst() const
{
  eval(QStringList() << "screenFirst()");
}

void UpKpr1ViewDcop::screenPrev() const
{
  eval(QStringList() << "screenPrev()");
}

void UpKpr1ViewDcop::screenNext() const
{
  eval(QStringList() << "screenNext()");
}

void UpKpr1ViewDcop::screenLast() const
{
  eval(QStringList() << "screenLast()");
}

void UpKpr1ViewDcop::screenSkip() const
{
  eval(QStringList() << "screenSkip()");
}

int UpKpr1ViewDcop::getCurrentPresPage() const
{
  return evalInt(QStringList() << "getCurrentPresPage()", 0);
}

int UpKpr1ViewDcop::getCurrentPresStep() const
{
  return evalInt(QStringList() << "getCurrentPresStep()", 0);
}

int UpKpr1ViewDcop::getNumPresPages() const
{
  return evalInt(QStringList() << "getNumPresPages()", 0);
}

int UpKpr1ViewDcop::getPresStepsOfPage() const
{
  return evalInt(QStringList() << "getPresStepsOfPage()", 0);
}

void UpKpr1ViewDcop::gotoPresPage(int pg) const
{
  QString pgStr;
  pgStr.setNum(pg);
  // Warning: An out of range argument kills kpresenter
  eval(QStringList() << "gotoPresPage(int)" << pgStr);
}

