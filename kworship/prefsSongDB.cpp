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
 * @file prefsSongDB.h
 * @brief SongDB preferences interface.
 * @author James Hogan <james@albanarts.com>
 */

#include "prefsSongDB.h"

/*
 * Constructors + destructor
 */

/// Primary constructor
prefsSongDB::prefsSongDB(QWidget *parent)
: QWidget(parent)
, Ui::prefsSongDB_base()
{
  setupUi(this);

  connect(kcfg_songdbType, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeDatabaseType(QString)));
  connect(buttonTest, SIGNAL(clicked()), this, SLOT(testConnectionSettings()));
}

/// Destructor.
prefsSongDB::~prefsSongDB()
{
}

/*
 * Slots
 */

/// Database type has changed.
void prefsSongDB::changeDatabaseType(QString newType)
{
  bool serverless = (newType == "SQLite");
  groupConnection->setVisible(!serverless);
  groupFile->setVisible(serverless);
}

/// Test connection settings.
#include <QtDebug>
void prefsSongDB::testConnectionSettings()
{
  qDebug() << __PRETTY_FUNCTION__;
}


