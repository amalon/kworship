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
 * @file KwSongdbVersion.cpp
 * @brief A song version from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdb.h"
#include "KwSongdbVersion.h"
#include "KwSongdbLyrics.h"
#include "KwSongdbLyricsOrder.h"

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
, m_lyricsLoaded(false)
, m_lyricsById()
, m_lyricsOrdersByOrder()
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
  {
    LyricsOrderIndex::iterator it;
    for (it = m_lyricsOrdersByOrder.begin(); it != m_lyricsOrdersByOrder.end(); ++it)
    {
      delete *it;
    }
  }

  {
    LyricsIndex::iterator it;
    for (it = m_lyricsById.begin(); it != m_lyricsById.end(); ++it)
    {
      delete *it;
    }
  }
}

/*
 * Accessors
 */

/// Get the song this is a version of.
KwSongdbSong* KwSongdbVersion::getSong()
{
  return m_song;
}

/// Get lyrics by id.
KwSongdbLyrics* KwSongdbVersion::getLyricsById(int id)
{
  loadLyrics();
  LyricsIndex::iterator it = m_lyricsById.find(id);
  if (it != m_lyricsById.end())
  {
    return *it;
  }
  else
  {
    return 0;
  }
}

/// Get lyrics by order.
KwSongdbLyrics* KwSongdbVersion::getLyricsByOrder(int order)
{
  loadLyrics();
  if (order >= 0 && order < m_lyricsOrdersByOrder.size())
  {
    return m_lyricsOrdersByOrder[order]->getLyrics();
  }
  else
  {
    return 0;
  }
}

/// Get number of lyric verses.
int KwSongdbVersion::getNumLyricsOrders()
{
  loadLyrics();
  return m_lyricsOrdersByOrder.size();
}

/// Get a lyrics order object.
KwSongdbLyricsOrder* KwSongdbVersion::getLyricsOrderByOrder(int order)
{
  loadLyrics();
  if (order >= 0 && order < m_lyricsOrdersByOrder.size())
  {
    return m_lyricsOrdersByOrder[order];
  }
  else
  {
    return 0;
  }
}

/// Get an ordered vector of lyrics.
QVector<KwSongdbLyrics*> KwSongdbVersion::getOrderedLyrics()
{
  loadLyrics();
  QVector<KwSongdbLyrics*> result;
  result.resize(m_lyricsOrdersByOrder.size());
  for (int i = 0; i < m_lyricsOrdersByOrder.size(); ++i)
  {
    result[i] = m_lyricsOrdersByOrder[i]->getLyrics();
  }
  return result;
}

/*
 * Helper functions
 */

/// Ensure that lyrics are loaded.
void KwSongdbVersion::loadLyrics()
{
  if (!m_lyricsLoaded)
  {
    QSqlQuery query(KwSongdb::self()->getDatabase());

    {
      // Get the lyrics data
      query.prepare("SELECT `id`, `lyrics` "
                    "FROM `SongLyrics` "
                    "WHERE `version_id` = ?");
      query.addBindValue(QVariant(m_id));
      bool worked = query.exec();
      assert(worked);

      // Copy the data
      while (query.next())
      {
        int id = query.value(0).toInt();
        QString lyrics = query.value(1).toString();
        m_lyricsById[id] = new KwSongdbLyrics(id, lyrics);
      }
    }

    {
      // Get the lyrics order data
      query.prepare("SELECT `order`, `lyrics_id`, `start_time`, `duration` "
                    "FROM `SongLyricsOrder` "
                    "WHERE `version_id` = ? "
                    "ORDER BY `order` ASC");
      query.addBindValue(QVariant(m_id));
      bool worked = query.exec();
      assert(worked);

      // Copy the data
      int nextOrder = 0;
      while (query.next())
      {
        int order = query.value(0).toInt();
        int lyrics_id = query.value(1).toInt();
        /// @todo get start_time and duration also
        assert(order == nextOrder);
        LyricsIndex::iterator it = m_lyricsById.find(lyrics_id);
        assert(it != m_lyricsById.end());
        m_lyricsOrdersByOrder.push_back(new KwSongdbLyricsOrder(order, *it));
        ++nextOrder;
      }
    }

    m_lyricsLoaded = true;
  }
}

