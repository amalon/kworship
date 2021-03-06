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
 * @file KwDatabaseSetup.cpp
 * @brief Database setup manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwDatabaseSetup.h"
#include "settings.h"

#include <kstandarddirs.h>

/*
 * Constructors + destructor
 */

/// Default constructor.
KwDatabaseSetup::KwDatabaseSetup(bool testing)
: m_testing(testing)
, m_database()
{
}

/// Destructor.
KwDatabaseSetup::~KwDatabaseSetup()
{
}

/*
 * Initialisation
 */

/// Initialise from configuration.
bool KwDatabaseSetup::initialiseFromConfig()
{
  int type = Settings::databaseType();
  switch (type)
  {
    case Settings::EnumDatabaseType::MySQL:
    case Settings::EnumDatabaseType::PostgreSQL:
      {
        QString strType;
        if (type == Settings::EnumDatabaseType::MySQL)
        {
          strType = "QMYSQL";
        }
        else
        {
          strType = "QPSQL";
        }
        return initialiseConnection(strType,
                                    Settings::databaseHost(),
                                    Settings::databaseName(),
                                    Settings::databaseUsername(),
                                    Settings::databasePassword());
      }
      break;
    case Settings::EnumDatabaseType::SQLite:
      {
        QString strType = "QSQLITE";
        QUrl url;
        if (Settings::databaseLocationCustom())
        {
          url = Settings::databaseLocation();
        }
        else
        {
          url = KStandardDirs::locateLocal("appdata", "kworship.db");
        }
        return initialiseFile(strType,
                              url);
      }
      break;
    default:
      break;
  }
  return false;
}

/// Initialise connection to a remote database.
bool KwDatabaseSetup::initialiseConnection(QString type, QString host, QString dbname, QString username, QString password)
{
  if (type != "QMYSQL" && type != "QPSQL")
  {
    return false;
  }

  // Setup connection
  if (m_testing)
  {
    m_database = QSqlDatabase::addDatabase(type, "test");
  }
  else
  {
    m_database = QSqlDatabase::addDatabase(type);
  }
  m_database.setHostName(host);
  m_database.setDatabaseName(dbname);
  m_database.setUserName(username);
  if (!password.isNull())
  {
    m_database.setPassword(password);
  }

  // Connect
  bool connected = m_database.open();

  if (connected && !m_testing)
  {
    // Ensure the database is setup ok
    /// @todo implement
  }

  return connected;
}

/// Initialise local file-based database.
bool KwDatabaseSetup::initialiseFile(QString type, QUrl url)
{
  if (type != "QSQLITE")
  {
    return false;
  }

  m_database = QSqlDatabase::addDatabase(type);
  m_database.setDatabaseName(url.toLocalFile());
  bool connected = m_database.open();

  if (connected)
  {
    // Ensure database is setup ok
    /// @todo implement
  }

  return connected;
}

/*
 * Accessors
 */

/// Get the database object.
QSqlDatabase& KwDatabaseSetup::database()
{
  return m_database;
}

