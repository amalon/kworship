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

#ifndef _KwArchive_h_
#define _KwArchive_h_

/**
 * @file KwArchive.h
 * @brief A KWorship data archive file.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwResourceManager.h"

#include <QStringList>

class KwDataFile;
class KwPlaylistList;

class KArchive;

class QIODevice;

/** A KWorship data archive file.
 * This class provides access to a KWorship archive file without loading all
 * the data into memory first.
 */
class KwArchive : public KwResourceManager
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwArchive(QIODevice* dev, bool writing);

    /// Primary constructor.
    KwArchive(const QString& fileName, bool writing);

    /// Destructor.
    virtual ~KwArchive();

    /*
     * Accessors
     */

    /// Get whether the archive is being written.
    bool isWriting() const;

    /// Get whether the archive is being read.
    bool isReading() const;

    /*
     * Main resource interface
     */

    virtual void addResource(const KwResourceLink* link);

    /*
     * Playlist data
     */

    /// Find how many playlists are in this archive.
    int numPlaylists();

    /// Get a list of playlist names in this archive.
    QStringList playlists();

    /// Create a new playlist from the archive.
    KwPlaylistList* extractPlaylist(QString name);

    /// Add a playlist to the archive.
    void addPlaylist(KwPlaylistList* playlist);

    /*
     * Access to song data
     */

    /// Find how many songs are in this archive.
    int numSongs();

    /// Get a list of song names in this archive.
    QStringList songs();

    /*
     * Access to generic resources
     */

    /// Find how many resources are in this archive.
    int numResources();

    /// Get a list of resource names in this archive.
    QStringList resources();

  protected:

    /*
     * Data files
     */

    /// Load a data file from the archive.
    KwDataFile* loadDataFile(QString path);

    /// Write a data file to the archive.
    void writeDataFile(QString path, const KwDataFile* data);

  private:

    /*
     * Variables
     */

    /// Whether we are in writing mode.
    bool m_writing;

    /// Compressor device.
    QIODevice* m_compressor;

    /// Archive object.
    KArchive* m_archive;

    /// Index data file.
    KwDataFile* m_index;

    /// Number of playlists.
    int m_numPlaylists;

};

#endif // _KwArchive_h_

