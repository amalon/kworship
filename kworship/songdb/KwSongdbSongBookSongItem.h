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

#ifndef _KwSongdbSongBookSongItem_h_
#define _KwSongdbSongBookSongItem_h_

/**
 * @file KwSongdbSongBookSongItem.h
 * @brief A list widget item for a song book song.
 * @author James Hogan <james@albanarts.com>
 */

#include <QObject>
#include <QListWidgetItem>

class KwSongdbVersion;
class KwSongdbSongBook;
class KwSongdbSongBookSong;

/// A list widget item for a song book song.
class KwSongdbSongBookSongItem : public QObject, public QListWidgetItem
{
    Q_OBJECT

  public:

    /*
     * Constructors + destructor
     */

    /// Construct a new song book song.
    KwSongdbSongBookSongItem(QListWidget* parent = 0);

    /// Construct from an existing song book song.
    KwSongdbSongBookSongItem(KwSongdbSongBookSong* songBookSong, QListWidget* parent = 0);

    /// Destructor.
    virtual ~KwSongdbSongBookSongItem();

    /*
     * Accessors
     */

    /// Get the song book.
    KwSongdbSongBook* songBook();

    /// Get the song book number
    int songNumber() const;

    /// Get the version.
    KwSongdbVersion* version();

  public slots:

    /*
     * Modifier slots
     */

    /// Save the changes to the song book object.
    void save(KwSongdbVersion* version);

    /// Set the song book.
    void setSongBook(KwSongdbSongBook* songBook);

    /// Set the song book number.
    void setSongNumber(int songNumber);

    /// Update the text.
    void updateText();

  private:

    /*
     * Variables
     */

    /// Song book song object.
    KwSongdbSongBookSong* m_songBookSong;

    /// Song book object.
    KwSongdbSongBook* m_songBook;

    /// Song book number.
    int m_songNumber;

    /// Version.
    KwSongdbVersion* m_version;

};

#endif // _KwSongdbSongBookSongItem_h_

