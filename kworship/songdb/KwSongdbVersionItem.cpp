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
 * @file KwSongdbVersionItem.cpp
 * @brief A list widget item for a song version.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbVersionItem.h"
#include "KwSongdbVersion.h"
#include "KwSongdbSongBookSongItem.h"

#include <KLocale>

/*
 * Constructors + destructor
 */

/// Construct a new song version.
KwSongdbVersionItem::KwSongdbVersionItem(QListWidget* parent)
: QObject()
, QListWidgetItem(i18n("Default version"), parent)
, m_version(0)
, m_name()
, m_writer()
, m_copyright()
, m_lyricsMarkup()
, m_songBookNumbers()
{
}

/// Construct from an existing song version.
KwSongdbVersionItem::KwSongdbVersionItem(KwSongdbVersion* version, QListWidget* parent)
: QObject()
, QListWidgetItem(version->niceName(), parent)
, m_version(version)
, m_name(version->name())
, m_writer(version->writer())
, m_copyright(version->copyright())
, m_lyricsMarkup(version->lyrics().markup())
, m_songBookNumbers()
{
  QList<KwSongdbSongBookSong*> songBookNumbers = version->songBookNumbers();
  foreach (KwSongdbSongBookSong* songBookNumber, songBookNumbers)
  {
    m_songBookNumbers.push_back(new KwSongdbSongBookSongItem(songBookNumber));
  }
}

/// Destructor.
KwSongdbVersionItem::~KwSongdbVersionItem()
{
  foreach (KwSongdbSongBookSongItem* songBookNumber, m_songBookNumbers)
  {
    delete songBookNumber;
  }
}

/*
 * Accessors
 */

/// Get the song version.
KwSongdbVersion* KwSongdbVersionItem::version()
{
  return m_version;
}

/// Get the version name.
QString KwSongdbVersionItem::versionName() const
{
  return m_name;
}

/// Get the name of the writer.
QString KwSongdbVersionItem::writer() const
{
  return m_writer;
}

/// Get the copyright notice.
QString KwSongdbVersionItem::copyright() const
{
  return m_copyright;
}

/// Get the lyrics markup.
QString KwSongdbVersionItem::lyricsMarkup() const
{
  return m_lyricsMarkup;
}

/// Get the list of song book number items.
QList<KwSongdbSongBookSongItem*> KwSongdbVersionItem::songBookNumbers()
{
  return m_songBookNumbers;
}

/*
 * Modifier slots
 */

/// Save the changes to the version object.
void KwSongdbVersionItem::save(KwSongdbSong* song)
{
  // Create new version if applicable
  if (0 == m_version)
  {
    m_version = new KwSongdbVersion(song);
  }

  m_version->setName(m_name);
  m_version->setWriter(m_writer);
  m_version->setCopyright(m_copyright);
  m_version->setLyricsMarkup(m_lyricsMarkup);
  m_version->save();

  // Now for the song book numbers
  foreach (KwSongdbSongBookSongItem* songBookNumber, m_songBookNumbers)
  {
    songBookNumber->save(m_version);
  }
}

/// Set the version name.
void KwSongdbVersionItem::setVersionName(const QString& name)
{
  m_name = name;
  setText(m_name.isEmpty() ? i18n("Default version") : name);
}

/// Set the name of the writer.
void KwSongdbVersionItem::setWriter(const QString& writer)
{
  m_writer = writer;
}

/// Set the copyright notice.
void KwSongdbVersionItem::setCopyright(const QString& copyright)
{
  m_copyright = copyright;
}

/// Set the lyrics markup.
void KwSongdbVersionItem::setLyricsMarkup(const QString& lyricsMarkup)
{
  m_lyricsMarkup = lyricsMarkup;
}

/// Add a song book number.
KwSongdbSongBookSongItem* KwSongdbVersionItem::addSongBookNumber()
{
  KwSongdbSongBookSongItem* item = new KwSongdbSongBookSongItem();
  m_songBookNumbers.push_back(item);
  return item;
}

