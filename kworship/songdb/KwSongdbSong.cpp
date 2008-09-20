/**
 * @file KwSongdbSong.cpp
 * @brief A song from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbSong.h"
#include "KwSongdb.h"

#include <QSqlQuery>
#include <QVariant>

#include <cassert>

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwSongdbSong::KwSongdbSong(int id)
: m_id(id)
, m_name()
{
  // Get the song version data
  QSqlQuery query(KwSongdb::self()->getDatabase());
  query.prepare("SELECT name, css_style_sheet_id "
                "FROM Song "
                "WHERE id = ?");
  query.addBindValue(QVariant(id));
  bool worked = query.exec();
  assert(worked);

  // Copy the data
  assert(query.first());
  m_name = query.value(0).toString();
}

/// Destructor.
KwSongdbSong::~KwSongdbSong()
{
}

/*
 * Accessors
 */

/// Get the id.
int KwSongdbSong::getId() const
{
  return m_id;
}

/// Get the name of the song.
QString KwSongdbSong::getName() const
{
  return m_name;
}

