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

#ifndef _UpKpr1Dcop_h_
#define _UpKpr1Dcop_h_

/**
 * @file UpKpr1Dcop.h
 * @brief DCOP interface using command line tool.
 * @author James Hogan <james@albanarts.com>
 */

#include <QStringList>

/// DCOP interface using command line tool.
class UpKpr1Dcop
{
  public:

    /*
     * Constructors + destructor
     */

    /// Default constructor.
    UpKpr1Dcop();

    /// Primary constructor.
    UpKpr1Dcop(const UpKpr1Dcop& parent, QString interface);

    /// Construct from dcop reference.
    UpKpr1Dcop(QStringList reference);

    /// Destructor.
    virtual ~UpKpr1Dcop();

    /*
     * Main interface
     */

    /// Find whether its valid.
    bool isValid() const;

    /// Get the dcop reference.
    const QStringList& reference() const;

    /*
     * Helper methods
     */

    /// Get the result of a dcop query on this interface.
    QString eval(bool* const err = 0, QStringList tail = QStringList()) const;

    /// Perform a dcop query on this interface.
    QString eval(QStringList tail) const
    {
      return eval(0, tail);
    }

    /// Get the resulting list of strings from a dcop query
    QStringList evalList(bool* const err = 0, QStringList tail = QStringList()) const;

    /// Get the resulting integer from a dcop query
    int evalInt(bool* const err, QStringList tail) const;

    /// Get the resulting integer from a dcop query
    int evalInt(QStringList tail, int defaultValue) const
    {
      bool err;
      int result = evalInt(&err, tail);
      return (err ? defaultValue : result);
    }

    /// Get a dcop reference from a string.
    static UpKpr1Dcop dcopRefFromString(QString input);

    /// Get a single dcop reference from a dcop query.
    UpKpr1Dcop evalRef(QStringList tail) const;

    /// Get a list of dcop references from a dcop query.
    template <typename INTERFACE>
    QList<INTERFACE> evalRefs(QStringList tail) const
    {
      bool error;
      QStringList items = evalList(&error, tail);
      QList<INTERFACE> results;
      if (!error)
      {
        foreach (QString item, items)
        {
          UpKpr1Dcop ref = dcopRefFromString(item);
          if (ref.isValid())
          {
            results << ref;
          }
        }
      }
      return results;
    }

  private:

    /*
     * Variables
     */

    /// Is this reference valid?
    bool m_valid;

    /// DCOP reference.
    QStringList m_reference;

};

#endif // _UpKpr1Dcop_h_

