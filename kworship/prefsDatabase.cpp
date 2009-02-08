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
 * @file prefsDatabase.h
 * @brief Database preferences interface.
 * @author James Hogan <james@albanarts.com>
 */

#include "prefsDatabase.h"
#include "KwDatabaseSetup.h"

#include <QMessageBox>
#include <QSqlError>

/*
 * Constructors + destructor
 */

/// Primary constructor
prefsDatabase::prefsDatabase(QWidget *parent)
: QWidget(parent)
, Ui::prefsDatabase_base()
{
  setupUi(this);

  connect(kcfg_databaseType, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeDatabaseType(QString)));
  connect(buttonTest, SIGNAL(clicked()), this, SLOT(testConnectionSettings()));
  connect(kcfg_databaseLocationCustom, SIGNAL(toggled(bool)), frameLocationCustom, SLOT(setEnabled(bool)));
}

/// Destructor.
prefsDatabase::~prefsDatabase()
{
}

/*
 * Slots
 */

/// Database type has changed.
void prefsDatabase::changeDatabaseType(QString newType)
{
  bool serverless = (newType == "SQLite");
  groupConnection->setVisible(!serverless);
  groupFile->setVisible(serverless);
  if (serverless)
  {
    if (newType == "SQLite")
    {
      kcfg_databaseLocation->setFilter("*.db|SQLite Databases (*.db)");
    }
  }
}

/// Test connection settings.
void prefsDatabase::testConnectionSettings()
{
  KwDatabaseSetup setup(true);
  QString type = kcfg_databaseType->currentText();
  if (type == "MySQL")
  {
    type = "QMYSQL";
  }
  else if (type == "PostgreSQL")
  {
    type = "QPSQL";
  }
  QString host = kcfg_databaseHost->text();
  QString name = kcfg_databaseName->text();
  QString username = kcfg_databaseUsername->text();
  QString password = kcfg_databasePassword->text();
  bool worked = setup.initialiseConnection(type, host, name, username, password);

  if (worked)
  {
    QMessageBox::information(this, i18n("Success"), i18n("Successfully connected to the database using the provided settings."), QMessageBox::Ok);
  }
  else
  {
    QMessageBox::warning(this, i18n("Failure"), i18n("Could not connect to the database using the provided settings. Please check the settings and try again.\n\n%1", setup.database().lastError().text()), QMessageBox::Ok);
  }
}


