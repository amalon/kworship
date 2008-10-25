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

#include <cassert>

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
  assert(0 == s_singleton);
  s_singleton = this;
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
    m_songsById[id] = newSong;
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

