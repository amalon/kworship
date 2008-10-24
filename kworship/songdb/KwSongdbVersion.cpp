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
 * @file KwSongdbVersion.cpp
 * @brief A song version from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdb.h"
#include "KwSongdbVersion.h"

#include <KLocale>

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
, m_name()
, m_writer()
, m_copyright()
, m_lyrics()
{
  // Get the song version data
  QSqlQuery query(KwSongdb::self()->database());
  query.prepare("SELECT song_id, name, writer, copyright, lyrics, css_style_sheet_id "
                "FROM SongVersion "
                "WHERE id = ?");
  query.addBindValue(QVariant(id));
  bool worked = query.exec();
  assert(worked);

  // Copy the data
  assert(query.first());
  m_song = KwSongdb::self()->songById(query.value(0).toInt());
  m_name = query.value(1).toString();
  m_writer = query.value(2).toString();
  m_copyright = query.value(3).toString();
  m_lyrics.setMarkup(query.value(4).toString());
}

/// Destructor.
KwSongdbVersion::~KwSongdbVersion()
{
}

/*
 * Accessors
 */

/// Get the song this is a version of.
KwSongdbSong* KwSongdbVersion::song()
{
  return m_song;
}

/// Get the name of this version.
QString KwSongdbVersion::name() const
{
  return m_name;
}

/// Get a non-empty name of this version.
QString KwSongdbVersion::niceName() const
{
  if (m_name.isEmpty())
  {
    return i18n("Default version");
  }
  else
  {
    return m_name;
  }
}

/// Get the name of the writer.
QString KwSongdbVersion::writer() const
{
  return m_writer;
}

/// Get the copyright notice.
QString KwSongdbVersion::copyright() const
{
  return m_copyright;
}

/// Get the copyright notice.
const KwSongdbLyrics& KwSongdbVersion::lyrics() const
{
  return m_lyrics;
}

