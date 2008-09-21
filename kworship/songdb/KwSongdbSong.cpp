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
  query.prepare("SELECT `name`, `css_style_sheet_id` "
                "FROM `Song` "
                "WHERE `id` = ?");
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

