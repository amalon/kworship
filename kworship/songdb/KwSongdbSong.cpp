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
 * @file KwSongdbSong.cpp
 * @brief A song from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbSong.h"
#include "KwSongdbVersion.h"
#include "KwSongdb.h"

#include <QSqlQuery>
#include <QVariant>
#include <QStringList>

/*
 * Constructors + destructor
 */

/// Construct a new song for database insertion.
KwSongdbSong::KwSongdbSong()
: m_id(-1)
, m_modifiedFields(Name)
, m_name()
, m_alternateName()
, m_versionsLoaded(false)
, m_versionIds()
{
}

#include <QtDebug>
/// Construct from the database.
KwSongdbSong::KwSongdbSong(int id)
: m_id(id)
, m_modifiedFields(0)
, m_name()
, m_alternateName()
, m_versionsLoaded(false)
, m_versionIds()
{
  // Get the song data
  QSqlQuery query(KwSongdb::self()->database());
  query.prepare("SELECT `name`, `alternate_name`, `css_style_sheet_id` "
                "FROM `Song` "
                "WHERE `id` = ?");
  query.addBindValue(QVariant(id));
  KW_SONGDB_QUERY(query);

  // Copy the data
  if (!query.first())
  {
    qDebug() << "first failed, active:" << query.isActive() << ", select:" << query.isSelect();
    exit(1);
  }
  m_name = query.value(0).toString();
  m_alternateName = query.value(1).toString();

  // Register with songdb
  KwSongdb::self()->registerSong(this);
}

/// Destructor.
KwSongdbSong::~KwSongdbSong()
{
}

/*
 * Accessors
 */

/// Get the id.
int KwSongdbSong::id() const
{
  return m_id;
}

/// Get the name of the song.
QString KwSongdbSong::name() const
{
  return m_name;
}

/// Get the alternate name of the song.
QString KwSongdbSong::alternateName() const
{
  return m_alternateName;
}

/// Get list of song versions.
QList<KwSongdbVersion*> KwSongdbSong::versions()
{
  if (!m_versionsLoaded)
  {
    // Get the version ids
    QSqlQuery query(KwSongdb::self()->database());
    query.prepare("SELECT `id` "
                  "FROM `SongVersion` "
                  "WHERE `song_id` = ?");
    query.addBindValue(QVariant(m_id));
    KW_SONGDB_QUERY(query);

    if (query.first())
    {
      do {
        m_versionIds.push_back(query.value(0).toInt());
      } while (query.next());
    }

    m_versionsLoaded = true;
  }
  return KwSongdb::self()->songVersionsByIds(m_versionIds);
}

/*
 * Mutators
 */

/// Set the name.
void KwSongdbSong::setName(const QString& name)
{
  if (name != m_name)
  {
    m_modifiedFields |= Name;
    m_name = name;
  }
}

/// Set the alternate name.
void KwSongdbSong::setAlternateName(const QString& name)
{
  if (name != m_alternateName)
  {
    m_modifiedFields |= AlternateName;
    m_alternateName = name;
  }
}

/// Save changes to the song data.
void KwSongdbSong::save()
{
  QStringList fields;
  QList<QVariant> values;
  Fields handled;

  // Straightforward modifications

  if (m_modifiedFields.testFlag(Name))
  {
    handled |= Name;
    fields.push_back("`name`");
    values.push_back(QVariant(m_name));
  }
  if (m_modifiedFields.testFlag(AlternateName))
  {
    handled |= AlternateName;
    fields.push_back("`alternate_name`");
    values.push_back(QVariant(m_alternateName));
  }

  bool insertion = (m_id < 0);
  if (insertion || !fields.isEmpty())
  {
    QSqlQuery query(KwSongdb::self()->database());

    if (insertion)
    {
      // Insert a new row
      QString qs = QString::fromAscii("?,").repeated(fields.size());
      qs.chop(1);
      query.prepare("INSERT INTO `Song` (" + fields.join(",") + ")"
                    " VALUES (" + qs + ")");
    }
    else
    {
      for (int i = 0; i < fields.size(); ++i)
      {
        fields[i] += "=?";
      }
      query.prepare("UPDATE `Song` "
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
    KW_SONGDB_QUERY(query);

    // Update which fields are modified
    m_modifiedFields &= ~handled;

    // Update relevent objects
    if (insertion)
    {
      m_id = query.lastInsertId().toInt();
      KwSongdb::self()->registerSong(this);
    }
  }
}

/// Register a version object.
void KwSongdbSong::registerVersion(KwSongdbVersion* version)
{
  m_versionIds.push_back(version->id());
}

