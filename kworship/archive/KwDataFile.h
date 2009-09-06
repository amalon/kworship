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

#ifndef _KwDataFile_h_
#define _KwDataFile_h_

/**
 * @file KwDataFile.h
 * @brief A KWorship XML data file.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwResourceManager.h"

#include <QList>

class KwPlaylistItem;
class KwPlaylistList;

class QIODevice;
class QTextStream;
class QDomDocument;
class QDomElement;

/// A KWorship XML data file.
class KwDataFile : public KwResourceManager
{
  public:

    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwDataFile();

    /// Destructor.
    virtual ~KwDataFile();

    /*
     * Individual playlist items
     */

    /** Insert a set of playlist items.
     * @param items List of playlist items to insert.
     * @param resources Resource manager.
     */
    void insertPlaylistItems(const QList<KwPlaylistItem*>& items, KwResourceManager* resourceManager);

    /** Create a set of playlist items from the data.
     * @param resources Resource manager.
     * @returns Newly created playlist items which the user must delete.
     */
    QList<KwPlaylistItem*> extractPlaylistItems(KwResourceManager* resourceManager) const;

    /*
     * Playlists
     */

    /** Insert a playlist.
     * @param playlist Playlist to insert.
     * @param resources Resource manager.
     */
    void insertPlaylist(const KwPlaylistList* playlist, KwResourceManager* resourceManager);

    /** Create a playlist object from the data.
     * @param resources Resource manager.
     * @returns Newly created playlist which the user must delete.
     */
    KwPlaylistList* extractPlaylist(KwResourceManager* resourceManager) const;

    /*
     * Main resource interface
     */

    // Reimplemented
    virtual void addResource(const KwResourceLink* link);

    /*
     * Reading and writing
     */

    /// Read from device.
    void readFrom(QIODevice* device);

    /// Write to stream.
    void writeTo(QTextStream& stream) const;

  private:

    /*
     * Variables
     */

    /// DOM document.
    QDomDocument* m_domDocument;

};

#endif // _KwDataFile_h_

