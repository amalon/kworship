/**
 * @file KwSongdbVersion.cpp
 * @brief A song version from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbVersion.h"
#include "KwSongdb.h"

#include <QSqlQuery>
#include <QVariant>

#include <cassert>

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwSongdbVersion::KwSongdbVersion(int id)
: m_id(id)
, m_song(0)
{
  // Get the song version data
  QSqlQuery query(KwSongdb::self()->getDatabase());
  query.prepare("SELECT song_id, name, writer, copyright, css_style_sheet_id "
                "FROM SongVersion "
                "WHERE id = ?");
  query.addBindValue(QVariant(id));
  bool worked = query.exec();
  assert(worked);

  // Copy the data
  assert(query.first());
  m_song = KwSongdb::self()->getSongById(query.value(0).toInt());
}

/// Destructor.
KwSongdbVersion::~KwSongdbVersion()
{
}

/*
 * Accessors
 */

/// Get the song this is a version of.
KwSongdbSong* KwSongdbVersion::getSong()
{
  return m_song;
}

