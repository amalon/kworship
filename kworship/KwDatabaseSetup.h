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

#ifndef _KwDatabaseSetup_h_
#define _KwDatabaseSetup_h_

/**
 * @file KwDatabaseSetup.h
 * @brief Database setup manager.
 * @author James Hogan <james@albanarts.com>
 */

#include <QUrl>
#include <QSqlDatabase>

/// Database setup manager.
class KwDatabaseSetup
{
  public:

    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwDatabaseSetup(bool testing = false);

    /// Destructor.
    virtual ~KwDatabaseSetup();

    /*
     * Initialisation
     */

    /** Initialise from configuration.
     * @return Whether the initialisation succeeded.
     */
    bool initialiseFromConfig();

    /** Initialise connection to a remote database.
     * @param type "QMYSQL" or "QPSQL".
     * @param host Hostname of database server.
     * @param dbname Database name.
     * @param username Username to connect with.
     * @param password Password (set null if none).
     * @return Whether the initialisation succeeded.
     */
    bool initialiseConnection(QString type, QString host, QString dbname, QString username, QString password = QString());

    /** Initialise local file-based database.
     * @param type "QSQLITE".
     * @param url Url of database file.
     * @return Whether the initialisation succeeded.
     */
    bool initialiseFile(QString type, QUrl url);

    /*
     * Accessors
     */

    /// Get the database object.
    QSqlDatabase& database();

  private:

    /*
     * Variables
     */

    /** Testing mode.
     * This is for the test button in database configuration window.
     */
    bool m_testing;

    /// Database object.
    QSqlDatabase m_database;
};

#endif // _KwDatabaseSetup_h_

