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
 * @file UpKpr1Dcop.cpp
 * @brief DCOP interface using command line tool.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpKpr1Dcop.h"

#include <QProcess>

/*
 * Constructors + destructor
 */

/// Default constructor.
UpKpr1Dcop::UpKpr1Dcop()
: m_valid(false)
, m_reference()
{
}

/// Primary constructor.
UpKpr1Dcop::UpKpr1Dcop(const UpKpr1Dcop& parent, QString interface)
: m_valid(true)
, m_reference(parent.m_reference)
{
  m_reference << interface;
}

/// Construct from dcop reference.
UpKpr1Dcop::UpKpr1Dcop(QStringList reference)
: m_valid(true)
, m_reference(reference)
{
}

/// Destructor.
UpKpr1Dcop::~UpKpr1Dcop()
{
}

/*
 * Main interface
 */

/// Find whether its valid.
bool UpKpr1Dcop::isValid() const
{
  return m_valid;
}

/*
 * Helper methods
 */

/// Get the result of a dcop query on this interface.
QStringList UpKpr1Dcop::eval(bool& error, QStringList tail) const
{
  QStringList args = m_reference;
  args << tail;

  QProcess dcop;
  dcop.start("dcop", args);
  error = !dcop.waitForFinished();

  if (!error)
  {
    QString result = QString::fromAscii(dcop.readAll());
    return result.trimmed().split('\n');
  }
  else
  {
    return QStringList();
  }
}

/// Get a dcop reference from a string.
UpKpr1Dcop UpKpr1Dcop::dcopRefFromString(QString input)
{
#define DCOPREF_START "DCOPRef("
#define DCOPREF_END ")"
  if (input.startsWith(DCOPREF_START) && input.endsWith(DCOPREF_END))
  {
    return UpKpr1Dcop(input.mid(sizeof(DCOPREF_START)-1,
                                input.size() - (sizeof(DCOPREF_START)-1)
                                             - (sizeof(DCOPREF_END)-1)  ).split(','));
  }
  else
  {
    return UpKpr1Dcop();
  }
}

