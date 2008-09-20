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
}

/*
 * Accessors
 */

/// Get a song by id.
KwSongdbSong* KwSongdb::getSongById(int id)
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
KwSongdbVersion* KwSongdb::getSongVersionById(int id)
{
  VersionHash::iterator it = m_versionsById.find(id);
  if (it != m_versionsById.end())
  {
    return *it;
  }
  else
  {
    KwSongdbVersion* newVersion = new KwSongdbVersion(id);
    m_versionsById[id] = newVersion;
    return newVersion;
  }
}

