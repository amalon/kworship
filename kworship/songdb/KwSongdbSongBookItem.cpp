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
 * @file KwSongdbSongBookItem.cpp
 * @brief A list widget item for a song book.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbSongBookItem.h"
#include "KwSongdbSongBook.h"

#include <KLocale>

/*
 * Constructors + destructor
 */

/// Construct a new song book.
KwSongdbSongBookItem::KwSongdbSongBookItem(QListWidget* parent)
: QObject()
, QListWidgetItem(parent)
, m_songBook(0)
, m_abreviation()
, m_name()
, m_description()
{
  updateText();
}

/// Construct from an existing song book.
KwSongdbSongBookItem::KwSongdbSongBookItem(KwSongdbSongBook* songBook, QListWidget* parent)
: QObject()
, QListWidgetItem(parent)
, m_songBook(songBook)
, m_abreviation(songBook->abreviation())
, m_name(songBook->name())
, m_description(songBook->description())
{
  updateText();
}

/// Destructor.
KwSongdbSongBookItem::~KwSongdbSongBookItem()
{
}

/*
 * Accessors
 */

/// Get the song book.
KwSongdbSongBook* KwSongdbSongBookItem::songBook()
{
  return m_songBook;
}

/// Get the abreviation text.
QString KwSongdbSongBookItem::abreviation() const
{
  return m_abreviation;
}

/// Get the song book name.
QString KwSongdbSongBookItem::name() const
{
  return m_name;
}

/// Get the description.
QString KwSongdbSongBookItem::description() const
{
  return m_description;
}

/*
 * Modifier slots
 */

/// Save the changes to the song book object.
void KwSongdbSongBookItem::save()
{
  // Create new song book if applicable
  if (0 == m_songBook)
  {
    m_songBook = new KwSongdbSongBook();
  }

  m_songBook->setAbreviation(m_abreviation);
  m_songBook->setName(m_name);
  m_songBook->setDescription(m_description);
  m_songBook->save();
}

/// Set the abreviation text.
void KwSongdbSongBookItem::setAbreviation(const QString& abreviation)
{
  m_abreviation = abreviation;
  updateText();
}

/// Set the song book name.
void KwSongdbSongBookItem::setName(const QString& name)
{
  m_name = name;
  updateText();
}

/// Set the description.
void KwSongdbSongBookItem::setDescription(const QString& description)
{
  m_description = description;
}

/// Update the text.
void KwSongdbSongBookItem::updateText()
{
  setText(i18n("%1 - %2", m_abreviation, m_name));
}

