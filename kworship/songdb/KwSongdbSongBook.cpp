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
 * @file KwSongdbSongBook.cpp
 * @brief A song book of songs from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbSongBook.h"
#include "KwSongdb.h"

#include <QSqlQuery>
#include <QVariant>
#include <QStringList>

/*
 * Constructors + destructor
 */

/// Construct a new song book for database insertion.
KwSongdbSongBook::KwSongdbSongBook()
: m_id(-1)
, m_modifiedFields(Abreviation)
, m_abreviation()
, m_name()
, m_description()
{
}

/// Construct from the database.
KwSongdbSongBook::KwSongdbSongBook(int id)
: m_id(id)
, m_modifiedFields(0)
, m_abreviation()
, m_name()
, m_description()
{
  // Get the song book data
  QSqlQuery query(KwSongdb::self()->database());
  query.prepare("SELECT `abreviation`, `name`, `description` "
                "FROM `SongBook` "
                "WHERE `id` = ?");
  query.addBindValue(QVariant(id));
  bool worked = query.exec();
  Q_ASSERT(worked);

  // Copy the data
  Q_ASSERT(query.first());
  m_abreviation = query.value(0).toString();
  m_name = query.value(1).toString();
  m_description = query.value(2).toString();

  // Register with songdb
  KwSongdb::self()->registerSongBook(this);
}

/// Destructor.
KwSongdbSongBook::~KwSongdbSongBook()
{
}

/*
 * Accessors
 */

/// Get the id.
int KwSongdbSongBook::id() const
{
  return m_id;
}

/// Get the abreviation of the song book.
QString KwSongdbSongBook::abreviation() const
{
  return m_abreviation;
}

/// Get the name of the song book.
QString KwSongdbSongBook::name() const
{
  return m_name;
}

/// Get the description of the song book.
QString KwSongdbSongBook::description() const
{
  return m_description;
}

/*
 * Mutators
 */

/// Set the abreviation.
void KwSongdbSongBook::setAbreviation(const QString& abreviation)
{
  if (abreviation != m_abreviation)
  {
    m_modifiedFields |= Abreviation;
    m_abreviation = abreviation;
    /// @todo Update any songdb abreviation hash
  }
}

/// Set the name.
void KwSongdbSongBook::setName(const QString& name)
{
  if (name != m_name)
  {
    m_modifiedFields |= Name;
    m_name = name;
  }
}

/// Set the description.
void KwSongdbSongBook::setDescription(const QString& description)
{
  if (description != m_description)
  {
    m_modifiedFields |= Description;
    m_description = description;
  }
}

/// Save changes to the song book data.
void KwSongdbSongBook::save()
{
  QStringList fields;
  QList<QVariant> values;
  Fields handled;

  // Straightforward modifications

  if (m_modifiedFields.testFlag(Abreviation))
  {
    handled |= Abreviation;
    fields.push_back("`abreviation`=?");
    values.push_back(QVariant(m_abreviation));
  }

  if (m_modifiedFields.testFlag(Name))
  {
    handled |= Name;
    fields.push_back("`name`=?");
    values.push_back(QVariant(m_name));
  }

  if (m_modifiedFields.testFlag(Description))
  {
    handled |= Description;
    fields.push_back("`description`=?");
    values.push_back(QVariant(m_description));
  }

  bool insertion = (m_id < 0);
  if (insertion || !fields.isEmpty())
  {
    QSqlQuery query(KwSongdb::self()->database());

    if (insertion)
    {
      // Insert a new row
      query.prepare("INSERT INTO `SongBook` "
                    "SET " + fields.join(","));
    }
    else
    {
      query.prepare("UPDATE `SongBook` "
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
      KwSongdb::self()->registerSongBook(this);
    }
  }
}

