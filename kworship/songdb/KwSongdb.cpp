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
 * @file KwSongdb.cpp
 * @brief A song database manager class.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdb.h"
#include "KwSongdbSong.h"
#include "KwSongdbVersion.h"
#include "KwSongdbSongBook.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

/*
 * Singletonhood
 */

/// The one instance of this class.
KwSongdb* KwSongdb::s_singleton = 0;

/// Get the one instance of this class.
KwSongdb* KwSongdb::self()
{
  return s_singleton;
}

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwSongdb::KwSongdb(QSqlDatabase& db)
: m_database(db)
{
  Q_ASSERT(0 == s_singleton);
  s_singleton = this;

  /// @todo If any tables are missing, set them up
  /// @todo MYSQL: "SET GLOBAL sql_mode='ANSI';" to enable || instead of CONCAT
}

/// Destructor.
KwSongdb::~KwSongdb()
{
  s_singleton = 0;

  // Delete song versions
  {
    VersionHash::iterator it;
    for (it = m_versionsById.begin(); it != m_versionsById.end(); ++it)
    {
      delete *it;
    }
  }

  // Delete songs
  {
    SongHash::iterator it;
    for (it = m_songsById.begin(); it != m_songsById.end(); ++it)
    {
      delete *it;
    }
  }

}

/*
 * Functionality.
 */

#include <QtDebug>
bool KwSongdb::handleQuery(QSqlQuery &query, const char *src, int line)
{
  bool ok = query.exec();
  if (!ok)
  {
    qDebug() << "SQL QUERY FAILED:" << query.lastError().text();
  }
  else
  {
    qDebug() << "SQL QUERY SUCCEEDED!";
  }
  if (true || !ok)
  {
    if (0 != src && 0 != line)
    {
      qDebug() << "\tIn " << src << "#" << line;
    }
    qDebug() << "\tQUERY:" << query.executedQuery();
    //qDebug() << "\tEXECUTED QUERY:" << query.executedQuery();
    //qDebug() << "\tORIGINAL QUERY:" << query.lastQuery();
    qDebug() << "\tWITH BINDINGS:" << query.boundValues();
  }
  return ok;
}

/*
 * Accessors
 */

/// Get the database.
QSqlDatabase KwSongdb::database()
{
  return m_database;
}

/// Get a song by id.
KwSongdbSong* KwSongdb::songById(int id)
{
  SongHash::iterator it = m_songsById.find(id);
  if (it != m_songsById.end())
  {
    return *it;
  }
  else
  {
    KwSongdbSong* newSong = new KwSongdbSong(id);
    return newSong;
  }
}

/** Get a song version by id.
 * This prefetches the song the version is a part of.
 */
KwSongdbVersion* KwSongdb::songVersionById(int id)
{
  VersionHash::iterator it = m_versionsById.find(id);
  if (it != m_versionsById.end())
  {
    return *it;
  }
  else
  {
    KwSongdbVersion* newVersion = new KwSongdbVersion(id);
    return newVersion;
  }
}

/// Get song versions by ids.
QList<KwSongdbVersion*> KwSongdb::songVersionsByIds(const QList<int>& ids)
{
  QList<KwSongdbVersion*> list;
  foreach (int id, ids)
  {
    KwSongdbVersion* version = songVersionById(id);
    if (0 != version)
    {
      list.push_back(version);
    }
  }
  return list;
}

/// Get song book by id.
KwSongdbSongBook* KwSongdb::songBookById(int id)
{
  SongBookHash::iterator it = m_songBooksById.find(id);
  if (it != m_songBooksById.end())
  {
    return *it;
  }
  else
  {
    KwSongdbSongBook* newSongBook = new KwSongdbSongBook(id);
    return newSongBook;
  }
}

/// Get all song books.
QList<KwSongdbSongBook*> KwSongdb::songBooks()
{
  // First use a query to get all song book ids
  QSqlQuery query(m_database);
  query.prepare("SELECT `id` "
                "FROM `SongBook`");
  KW_SONGDB_QUERY(query);

  // Then load them individually into a list
  QList<KwSongdbSongBook*> songBooks;
  if (query.first())
  {
    do {
      songBooks.push_back(songBookById(query.value(0).toInt()));
    } while (query.next());
  }
  return songBooks;
}

/*
 * Mutators
 */

/// Register a song object.
void KwSongdb::registerSong(KwSongdbSong* song)
{
  Q_ASSERT(m_songsById.constFind(song->id()) == m_songsById.constEnd());
  m_songsById[song->id()] = song;
}

/// Register a version object.
void KwSongdb::registerVersion(KwSongdbVersion* version)
{
  Q_ASSERT(m_versionsById.constFind(version->id()) == m_versionsById.constEnd());
  m_versionsById[version->id()] = version;
}

/// Register a song book.
void KwSongdb::registerSongBook(KwSongdbSongBook* songBook)
{
  Q_ASSERT(m_songBooksById.constFind(songBook->id()) == m_songBooksById.constEnd());
  m_songBooksById[songBook->id()] = songBook;
}

