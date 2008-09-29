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
 * @file KwDatabaseSetup.cpp
 * @brief A song database manager class.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwDatabaseSetup.h"
#include "settings.h"

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
  int type = Settings::songdbType();
  switch (type)
  {
    case Settings::EnumSongdbType::MySQL:
    case Settings::EnumSongdbType::PostgreSQL:
      {
        QString strType;
        if (type == Settings::EnumSongdbType::MySQL)
        {
          strType = "QMYSQL";
        }
        else
        {
          strType = "QPSQL";
        }
        return initialiseConnection(strType,
                                    Settings::songdbHost(),
                                    Settings::songdbName(),
                                    Settings::songdbUsername(),
                                    Settings::songdbPassword());
      }
      break;
    case Settings::EnumSongdbType::SQLite:
      {
        QString strType = "QSQLITE";
        QUrl url;
        if (Settings::songdbLocationCustom())
        {
          url = Settings::songdbLocation();
        }
        else
        {
          /// @todo Use kde apps dir as default location
          url = QUrl("file://~/kworship.db");
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

  /// @todo Implement
  Q_UNUSED(url)

  return false;
}

/*
 * Accessors
 */

/// Get the database object.
QSqlDatabase& KwDatabaseSetup::database()
{
  return m_database;
}

