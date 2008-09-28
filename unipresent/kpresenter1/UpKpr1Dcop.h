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

  protected:

    /*
     * Helper methods
     */

    /// Get the result of a dcop query on this interface.
    QStringList eval(bool& err, QStringList tail = QStringList()) const;

    /// Get a dcop reference from a string.
    static UpKpr1Dcop dcopRefFromString(QString input);

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

