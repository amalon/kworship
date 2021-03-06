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

#ifndef _KwSongdbSongEditWidget_h_
#define _KwSongdbSongEditWidget_h_

/**
 * @file KwSongdbSongEditWidget.h
 * @brief Widget for editing a song.
 * @author James Hogan <james@albanarts.com>
 */

#include "ui_KwSongdbSongEditWidget_base.h"

#include <QWidget>

class KwSongdbSong;
class KwSongdbVersion;
class KwSongdbVersionItem;
class KwSongdbSongBook;

/** Widget for editing a song.
 * Allows editing of song information, song versions and lyrics.
 */
class KwSongdbSongEditWidget : public QWidget, public Ui::KwSongdbSongEditWidget_base
{
    Q_OBJECT

  public:

    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwSongdbSongEditWidget();

    /// Destructor.
    virtual ~KwSongdbSongEditWidget();

  public slots:

    /*
     * Saving and loading
     */

    /// Load from database.
    void load(KwSongdbSong* song, KwSongdbVersion* selectedVersion = 0);

    /// Save to database.
    void save();

    /// Add a song version.
    void addVersion();

  signals:

    /*
     * Signals
     */

    /// Emitted when the lyrics markup has changed.
    void lyricsMarkupChangedSignal(const QString& lyricsMarkup);

    /// Emitted when the song book is changed.
    void songBookChangedSignal(KwSongdbSongBook* songBook);

    /// Emitted when the changed state of the form changes.
    void changed(bool changed);

  private slots:

    /*
     * Private slots
     */

    /// A different version has been selected.
    void versionChanged(QListWidgetItem* current, QListWidgetItem* previous);

    /// A different song book number has been selected.
    void songBookNumberChanged(QListWidgetItem* current, QListWidgetItem* previous);

    /// Lyrics markup edit box has been modified.
    void lyricsMarkupChanged();

    /// Selected song book has changed.
    void songBookChanged(int index);

    /// Button to edit song books has been clicked.
    void editSongBooksClicked();

    /// Update the list of song books.
    void updateSongBooks();

    /// Add a song book number to the version.
    void addSongBookNumber();

    /// Remove the selected song book number.
    void removeSongBookNumber();

  private:

    /*
     * Variables
     */

    /// Song object.
    KwSongdbSong* m_song;

    /// Current version.
    KwSongdbVersionItem* m_currentVersion;

};

#endif // _KwSongdbSongEditWidget_h_
