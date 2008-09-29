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
#include "KwDatabaseSetup.h"

#include <QMessageBox>

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
  connect(kcfg_songdbLocationCustom, SIGNAL(toggled(bool)), frameLocationCustom, SLOT(setEnabled(bool)));
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
  if (serverless)
  {
    if (newType == "SQLite")
    {
      kcfg_songdbLocation->setFilter("*.db|SQLite Databases (*.db)");
    }
  }
}

/// Test connection settings.
void prefsSongDB::testConnectionSettings()
{
  KwDatabaseSetup setup(true);
  QString type = kcfg_songdbType->currentText();
  if (type == "MySQL")
  {
    type = "QMYSQL";
  }
  else if (type == "PostgreSQL")
  {
    type = "QPSQL";
  }
  QString host = kcfg_songdbHost->text();
  QString name = kcfg_songdbName->text();
  QString username = kcfg_songdbUsername->text();
  QString password = kcfg_songdbPassword->text();
  bool worked = setup.initialiseConnection(type, host, name, username, password);

  if (worked)
  {
    QMessageBox::information(this, i18n("Success"), i18n("Successfully connected to the database using the provided settings."), QMessageBox::Ok);
  }
  else
  {
    QMessageBox::warning(this, i18n("Failure"), i18n("Could not connect to the database using the provided settings. Please check the settings and try again."), QMessageBox::Ok);
  }
}


