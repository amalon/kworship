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
 * @file KwSongdbSongBookSongItem.cpp
 * @brief A list widget item for a song book song.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbSongBookSongItem.h"
#include "KwSongdbSongBookSong.h"
#include "KwSongdbSongBook.h"

#include <KLocale>

/*
 * Constructors + destructor
 */

/// Construct a new song book song.
KwSongdbSongBookSongItem::KwSongdbSongBookSongItem(QListWidget* parent)
: QObject()
, QListWidgetItem(parent)
, m_songBookSong(0)
, m_songBook(0)
, m_songNumber(1)
, m_version(0)
{
  updateText();
}

/// Construct from an existing song book song.
KwSongdbSongBookSongItem::KwSongdbSongBookSongItem(KwSongdbSongBookSong* songBookSong, QListWidget* parent)
: QObject()
, QListWidgetItem(parent)
, m_songBookSong(songBookSong)
, m_songBook(songBookSong->songBook())
, m_songNumber(songBookSong->songNumber())
, m_version(songBookSong->version())
{
  updateText();
}

/// Destructor.
KwSongdbSongBookSongItem::~KwSongdbSongBookSongItem()
{
}

/*
 * Accessors
 */

/// Get the song book.
KwSongdbSongBook* KwSongdbSongBookSongItem::songBook()
{
  return m_songBook;
}

/// Get the song book number
int KwSongdbSongBookSongItem::songNumber() const
{
  return m_songNumber;
}

/// Get the version.
KwSongdbVersion* KwSongdbSongBookSongItem::version()
{
  return m_version;
}

/*
 * Modifier slots
 */

/// Save the changes to the song book object.
void KwSongdbSongBookSongItem::save()
{
  // Create new song book song if applicable
  if (0 == m_songBookSong)
  {
    m_songBookSong = new KwSongdbSongBookSong();
  }

  m_songBookSong->setSongBook(m_songBook);
  m_songBookSong->setSongNumber(m_songNumber);
  m_songBookSong->setVersion(m_version);
  m_songBookSong->save();
}

/// Set the song book.
void KwSongdbSongBookSongItem::setSongBook(KwSongdbSongBook* songBook)
{
  m_songBook = songBook;
  updateText();
}

/// Set the song book number.
void KwSongdbSongBookSongItem::setSongNumber(int songNumber)
{
  m_songNumber = songNumber;
  updateText();
}

/// Set the song version at this song book number.
void KwSongdbSongBookSongItem::setVersion(KwSongdbVersion* version)
{
  m_version = version;
}

/// Update the text.
void KwSongdbSongBookSongItem::updateText()
{
  setText(i18n("%1 #%2", m_songBook->abreviation(), m_songNumber));
}

