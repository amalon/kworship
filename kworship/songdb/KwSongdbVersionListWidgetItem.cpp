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
 * @file KwSongdbVersionListWidgetItem.cpp
 * @brief A list widget item for a song version.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbVersionListWidgetItem.h"
#include "KwSongdbVersion.h"

#include <KLocale>

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwSongdbVersionListWidgetItem::KwSongdbVersionListWidgetItem(KwSongdbVersion* version, QListWidget* parent)
: QObject()
, QListWidgetItem(version->niceName(), parent)
, m_version(version)
, m_name(version->name())
, m_writer(version->writer())
, m_copyright(version->copyright())
{
}

/// Destructor.
KwSongdbVersionListWidgetItem::~KwSongdbVersionListWidgetItem()
{
}

/*
 * Accessors
 */

/// Get the song version id.
KwSongdbVersion* KwSongdbVersionListWidgetItem::version()
{
  return m_version;
}

/// Get the version name.
QString KwSongdbVersionListWidgetItem::versionName() const
{
  return m_name;
}

/// Get the name of the writer.
QString KwSongdbVersionListWidgetItem::writer() const
{
  return m_writer;
}

/// Get the copyright notice.
QString KwSongdbVersionListWidgetItem::copyright() const
{
  return m_copyright;
}

/*
 * Modifier slots
 */

/// Set the version name.
void KwSongdbVersionListWidgetItem::setVersionName(const QString& name)
{
  m_name = name;
  setText(m_name.isEmpty() ? i18n("Default version") : name);
}

/// Set the name of the writer.
void KwSongdbVersionListWidgetItem::setWriter(const QString& writer)
{
  m_writer = writer;
}

/// Set the copyright notice.
void KwSongdbVersionListWidgetItem::setCopyright(const QString& copyright)
{
  m_copyright = copyright;
}

