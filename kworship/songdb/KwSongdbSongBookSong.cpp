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
 * @file KwSongdbSongBookSong.cpp
 * @brief A song book song from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbSongBookSong.h"
#include "KwSongdbSongBook.h"
#include "KwSongdbVersion.h"
#include "KwSongdb.h"

#include <QStringList>
#include <QSqlQuery>
#include <QVariant>

/*
 * Constructors + destructor
 */

/// Construct a new song book song for database insertion.
KwSongdbSongBookSong::KwSongdbSongBookSong()
: m_originalSongBookId(-1)
, m_originalSongNumber(-1)
, m_songBook(0)
, m_songNumber(1)
, m_version(0)
{
}

/// Construct from the database from data.
KwSongdbSongBookSong::KwSongdbSongBookSong(KwSongdbSongBook* songBook, int songNumber, KwSongdbVersion* version)
: m_originalSongBookId(songBook->id())
, m_originalSongNumber(songNumber)
, m_songBook(songBook)
, m_songNumber(songNumber)
, m_version(version)
{
}

/// Destructor.
KwSongdbSongBookSong::~KwSongdbSongBookSong()
{
}

/*
 * Accessors
 */

/// Get the song book.
KwSongdbSongBook* KwSongdbSongBookSong::songBook()
{
  return m_songBook;
}

/// Get the song number in the song book.
int KwSongdbSongBookSong::songNumber() const
{
  return m_songNumber;
}

/// Get the song version.
KwSongdbVersion* KwSongdbSongBookSong::version()
{
  return m_version;
}

/*
 * Mutators
 */

/// Set the song book.
void KwSongdbSongBookSong::setSongBook(KwSongdbSongBook* songBook)
{
  if (songBook != m_songBook)
  {
    m_modifiedFields |= SongBook;
    m_songBook = songBook;
  }
}

/// Set the song number in the song book.
void KwSongdbSongBookSong::setSongNumber(int songNumber)
{
  if (songNumber != m_songNumber)
  {
    m_modifiedFields |= SongNumber;
    m_songNumber = songNumber;
  }
}

/// Set the song version.
void KwSongdbSongBookSong::setVersion(KwSongdbVersion* version)
{
  if (version != m_version)
  {
    m_modifiedFields |= Version;
    m_version = version;
  }
}

/// Save changes to the song book data.
void KwSongdbSongBookSong::save()
{
  QStringList fields;
  QList<QVariant> values;
  Fields handled;

  // Straightforward modifications

  if (m_modifiedFields.testFlag(SongBook))
  {
    handled |= SongBook;
    fields.push_back("`book_id`=?");
    values.push_back(QVariant(m_songBook->id()));
  }

  if (m_modifiedFields.testFlag(SongNumber))
  {
    handled |= SongNumber;
    fields.push_back("`book_number`=?");
    values.push_back(QVariant(m_songNumber));
  }

  if (m_modifiedFields.testFlag(Version))
  {
    handled |= Version;
    fields.push_back("`version_id`=?");
    values.push_back(QVariant(m_version->id()));
  }

  bool insertion = (m_originalSongBookId < 0);
  if (insertion || !fields.isEmpty())
  {
    QSqlQuery query(KwSongdb::self()->database());

    if (insertion)
    {
      // Insert a new row
      query.prepare("INSERT INTO `SongBookSong` "
                    "SET " + fields.join(","));
    }
    else
    {
      query.prepare("UPDATE `SongBookSong` "
                    "SET " + fields.join(",") + " "
                    "WHERE book_id = ? AND book_number = ?");
      values.push_back(QVariant(m_originalSongBookId));
      values.push_back(QVariant(m_originalSongNumber));
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
      m_originalSongBookId = m_songBook->id();
      m_originalSongNumber = m_songNumber;
    }
  }
}

