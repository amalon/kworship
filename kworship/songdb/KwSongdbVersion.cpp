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

#include "KwSongdbVersion.h"
#include "KwSongdbSong.h"
#include "KwSongdbSongBookSong.h"
#include "KwSongdb.h"

#include <KLocale>

#include <QSqlQuery>
#include <QVariant>

/*
 * Constructors + destructor
 */

/// Construct a new version for database insertion.
KwSongdbVersion::KwSongdbVersion(KwSongdbSong* song)
: m_id(-1)
, m_song(song)
, m_modifiedFields(0)
, m_name()
, m_writer()
, m_copyright()
, m_lyrics()
, m_songBookNumbersLoaded(false)
, m_songBookNumbers()
{
}

/// Construct from the database.
KwSongdbVersion::KwSongdbVersion(int id)
: m_id(id)
, m_song(0)
, m_modifiedFields(0)
, m_name()
, m_writer()
, m_copyright()
, m_lyrics()
, m_songBookNumbersLoaded(false)
, m_songBookNumbers()
{
  // Get the song version data
  QSqlQuery query(KwSongdb::self()->database());
  query.prepare("SELECT `song_id`, `name`, `writer`, `copyright`, `lyrics`, `css_style_sheet_id` "
                "FROM `SongVersion` "
                "WHERE `id` = ?");
  query.addBindValue(QVariant(id));
  bool worked = query.exec();
  Q_ASSERT(worked);

  // Copy the data
  Q_ASSERT(query.first());
  m_song = KwSongdb::self()->songById(query.value(0).toInt());
  m_name = query.value(1).toString();
  m_writer = query.value(2).toString();
  m_copyright = query.value(3).toString();
  m_lyrics.setMarkup(query.value(4).toString());

  // Register with songdb
  KwSongdb::self()->registerVersion(this);
}

/// Destructor.
KwSongdbVersion::~KwSongdbVersion()
{
}

/*
 * Accessors
 */

/// Get the version id.
int KwSongdbVersion::id()
{
  return m_id;
}

/// Get the song this is a version of.
KwSongdbSong* KwSongdbVersion::song() const
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

/// Get song book numbers.
QList<KwSongdbSongBookSong*> KwSongdbVersion::songBookNumbers()
{
  if (!m_songBookNumbersLoaded)
  {
    Q_ASSERT(m_id >= 0);

    // Get the song version data
    QSqlQuery query(KwSongdb::self()->database());
    query.prepare("SELECT `book_id`, `book_number` "
                  "FROM `SongBookSong` "
                  "WHERE `version_id` = ?");
    query.addBindValue(QVariant(m_id));
    bool worked = query.exec();
    Q_ASSERT(worked);

    m_songBookNumbersLoaded = true;

    // Copy the data
    if (query.first())
    {
      do {
        int bookId = query.value(0).toInt();
        int bookNumber = query.value(1).toInt();
        KwSongdbSongBook* songBook = KwSongdb::self()->songBookById(bookId);
        m_songBookNumbers.push_back(new KwSongdbSongBookSong(songBook, bookNumber, this));
      } while (query.next());
    }
  }
  return m_songBookNumbers;
}

/*
 * Mutators
 */

/// Set the name.
void KwSongdbVersion::setName(const QString& name)
{
  if (name != m_name)
  {
    m_modifiedFields |= Name;
    m_name = name;
  }
}

/// Set the writer.
void KwSongdbVersion::setWriter(const QString& writer)
{
  if (writer != m_writer)
  {
    m_modifiedFields |= Writer;
    m_writer = writer;
  }
}

/// Set the copyright notice.
void KwSongdbVersion::setCopyright(const QString& copyright)
{
  if (copyright != m_copyright)
  {
    m_modifiedFields |= Copyright;
    m_copyright = copyright;
  }
}

/// Set the lyrics markup.
void KwSongdbVersion::setLyricsMarkup(const QString& markup)
{
  if (markup != m_lyrics.markup())
  {
    m_modifiedFields |= Lyrics;
    m_lyrics.setMarkup(markup);
  }
}

/// Set the lyrics plain text verses.
void KwSongdbVersion::setLyricsPlainVerses(const QStringList& plainVerses)
{
  if (plainVerses != m_lyrics.plainVerses())
  {
    m_modifiedFields |= Lyrics;
    m_lyrics.setPlainVerses(plainVerses);
  }
}

/// Set the lyrics.
void KwSongdbVersion::setLyrics(const KwSongdbLyrics& lyrics)
{
  if (lyrics != m_lyrics)
  {
    m_modifiedFields |= Lyrics;
    m_lyrics = lyrics;
  }
}

/// Save changes to the version data.
void KwSongdbVersion::save()
{
  QStringList fields;
  QList<QVariant> values;
  Fields handled;

  // Straightforward modifications

  if (m_modifiedFields.testFlag(Name))
  {
    handled |= Name;
    fields.push_back("`name`=?");
    values.push_back(QVariant(m_name));
  }

  if (m_modifiedFields.testFlag(Writer))
  {
    handled |= Writer;
    fields.push_back("`writer`=?");
    values.push_back(QVariant(m_writer));
  }

  if (m_modifiedFields.testFlag(Copyright))
  {
    handled |= Copyright;
    fields.push_back("`copyright`=?");
    values.push_back(QVariant(m_copyright));
  }

  if (m_modifiedFields.testFlag(Lyrics))
  {
    handled |= Lyrics;
    fields.push_back("`lyrics`=?");
    values.push_back(QVariant(m_lyrics.markup()));
  }

  bool insertion = (m_id < 0);
  if (insertion || !fields.isEmpty())
  {
    QSqlQuery query(KwSongdb::self()->database());

    if (insertion)
    {
      // Insert a new row
      fields.push_back("`song_id`=?");
      values.push_back(QVariant(m_song->id()));
      query.prepare("INSERT INTO `SongVersion` "
                    "SET " + fields.join(","));
    }
    else
    {
      query.prepare("UPDATE `SongVersion` "
                    "SET " + fields.join(",") + " "
                    "WHERE id = ?");
      values.push_back(QVariant(m_id));
    }

    // Add bind values
    foreach (QVariant value, values)
    {
      query.addBindValue(value);
    }

    // Execute query
    bool worked = query.exec();
    Q_ASSERT(worked);

    // Update which fields are modified
    m_modifiedFields &= ~handled;

    // Update relevent objects
    if (insertion)
    {
      m_id = query.lastInsertId().toInt();
      KwSongdb::self()->registerVersion(this);
      m_song->registerVersion(this);
    }
  }
}

