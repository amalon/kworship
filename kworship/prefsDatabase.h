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

#ifndef _prefsDatabase_h_
#define _prefsDatabase_h_

/**
 * @file prefsDatabase.h
 * @brief Database preferences interface.
 * @author James Hogan <james@albanarts.com>
 */

#include <QtGui/QWidget>

#include "ui_prefsDatabase_base.h"

/// Database preferences interface.
class prefsDatabase : public QWidget, public Ui::prefsDatabase_base
{
  Q_OBJECT
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    prefsDatabase(QWidget *parent);

    /// Destructor.
    virtual ~prefsDatabase();

  private slots:

    /*
     * Slots
     */

    /// Database type has changed.
    void changeDatabaseType(QString newType);

    /// Test connection settings.
    void testConnectionSettings();
};

#endif // _prefsDatabase_h_
