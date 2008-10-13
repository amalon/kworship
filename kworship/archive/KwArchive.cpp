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
 * @file KwArchive.cpp
 * @brief A KWorship data archive file.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwArchive.h"
#include "KwDataFile.h"

#include <KTar>
#include <KFilterDev>

#include <QFile>
#include <QTextStream>

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwArchive::KwArchive(QIODevice* dev, bool writing)
: m_writing(writing)
, m_compressor(0)
, m_archive(0)
, m_index(0)
, m_numPlaylists(-1)
{
  // Compression
  m_compressor = KFilterDev::device(dev, "application/x-gzip", false);
  m_compressor->open(writing ? QFile::WriteOnly : QFile::ReadOnly);
  // Archiving
  m_archive = new KTar(m_compressor);
  m_archive->open(writing ? QFile::WriteOnly : QFile::ReadOnly);

  if (!writing)
  {
    m_index = loadDataFile("index.kw");
  }
  else
  {
    m_index = new KwDataFile();
  }
}

/// Destructor.
KwArchive::~KwArchive()
{
  // Finally we need to write out the index file
  writeDataFile("index.kw", m_index);
  delete m_index;

  // Now its safe to close the archive
  m_archive->close();
  delete m_archive;
  m_compressor->close();
  delete m_compressor;
}

/*
 * Accessors
 */

/// Get whether the archive is being written.
bool KwArchive::isWriting() const
{
  return m_writing;
}

/// Get whether the archive is being read.
bool KwArchive::isReading() const
{
  return !m_writing;
}

/*
 * Playlist data
 */

/// Find how many playlists are in this archive.
int KwArchive::numPlaylists()
{
  return 0;
}

/// Get a list of playlist names in this archive.
QStringList KwArchive::playlists()
{
  return QStringList();
}

/// Add a playlist to the archive.
void KwArchive::addPlaylist(KwPlaylistList* playlist)
{
  Q_ASSERT(isWriting());

  KwDataFile* playlistFile = new KwDataFile();
  playlistFile->insertPlaylist(playlist, 0);
  writeDataFile(QString("playlists/%1.kw").arg(++m_numPlaylists),
                playlistFile);
  delete playlistFile;
}

/*
 * Access to song data
 */

/// Find how many songs are in this archive.
int KwArchive::numSongs()
{
  return 0;
}

/// Get a list of song names in this archive.
QStringList KwArchive::songs()
{
  return QStringList();
}

/*
 * Access to generic resources
 */

/// Find how many resources are in this archive.
int KwArchive::numResources()
{
  return 0;
}

/// Get a list of resource names in this archive.
QStringList KwArchive::resources()
{
  return QStringList();
}

/*
 * Data files
 */

/// Load a data file from the archive.
KwDataFile* KwArchive::loadDataFile(QString path)
{
  Q_ASSERT(isReading());

  // Look for the entry
  const KArchiveEntry* entry = m_archive->directory()->entry(path);
  if (0 == entry || !entry->isFile())
  {
    return 0;
  }

  // Turn entry into a file
  const KArchiveFile* fileEntry = dynamic_cast<const KArchiveFile*>(entry);
  Q_ASSERT(fileEntry); // isFile() should mean entry is a KArchiveFile

  // Load into a KwDataFile object
  QIODevice* fileDevice = fileEntry->createDevice();
  KwDataFile* dataFile = new KwDataFile();
  dataFile->readFrom(fileDevice);
  delete fileDevice;

  return dataFile;
}

/// Write a data file to the archive.
void KwArchive::writeDataFile(QString path, const KwDataFile* data)
{
  Q_ASSERT(isWriting());

  // Get the raw xml data
  QByteArray xmlData;
  {
    QTextStream stream(&xmlData);
    data->writeTo(stream);
  }

  // Write this to the archive
  m_archive->writeFile(path, "user", "group", xmlData, xmlData.size());
}

