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
QString UpKpr1Dcop::eval(bool* const error, QStringList tail) const
{
  QStringList args = m_reference;
  args << tail;

  QProcess dcop;
  dcop.start("dcop", args);
  bool localError = !dcop.waitForFinished();
  if (0 != error)
  {
    *error = localError;
  }

  if (!localError)
  {
    QString result = QString::fromAscii(dcop.readAll());
    if (result.endsWith('\n'))
    {
      result = result.left(result.size()-1);
    }
    return result;
  }
  else
  {
    return QString();
  }
}

/// Get the resulting list of strings from a dcop query
QStringList UpKpr1Dcop::evalList(bool* const err, QStringList tail) const
{
  return eval(err,tail).split('\n');
}

/// Get the resulting integer from a dcop query
int UpKpr1Dcop::evalInt(bool* const err, QStringList tail) const
{
  bool evalErr;
  int result;
  QString string = eval(&evalErr, tail);
  if (!evalErr)
  {
    result = string.toInt(&evalErr);
    evalErr = !evalErr;
    if (evalErr)
    {
      result = 0;
    }
  }
  else
  {
    result = 0;
  }
  if (0 != err)
  {
    *err = evalErr;
  }
  return result;
}

/// Get a dcop reference from a string.
UpKpr1Dcop UpKpr1Dcop::dcopRefFromString(QString input)
{
#define DCOPREF_START "DCOPRef("
#define DCOPREF_END ")"
#define DCOPREF_NULL DCOPREF_START "," DCOPREF_END
  if (input.startsWith(DCOPREF_START) &&
      input.endsWith(DCOPREF_END) &&
      input != DCOPREF_NULL)
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

/// Get a single dcop reference from a dcop query.
UpKpr1Dcop UpKpr1Dcop::evalRef(QStringList tail) const
{
  bool error;
  QStringList items = evalList(&error, tail);
  if (!error && items.size() == 1)
  {
    return dcopRefFromString(items.first());
  }
  return UpKpr1Dcop();
}
