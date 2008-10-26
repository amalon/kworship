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

#ifndef _KwSongdbVersionItem_h_
#define _KwSongdbVersionItem_h_

/**
 * @file KwSongdbVersionItem.h
 * @brief A list widget item for a song version.
 * @author James Hogan <james@albanarts.com>
 */

#include <QObject>
#include <QListWidgetItem>
#include <QString>
#include <QList>

class KwSongdbSong;
class KwSongdbVersion;
class KwSongdbSongBookSongItem;

/// A list widget item for a song version.
class KwSongdbVersionItem : public QObject, public QListWidgetItem
{
    Q_OBJECT

  public:

    /*
     * Constructors + destructor
     */

    /// Construct a new song version.
    KwSongdbVersionItem(QListWidget* parent = 0);

    /// Construct from an existing song version.
    KwSongdbVersionItem(KwSongdbVersion* version, QListWidget* parent = 0);

    /// Destructor.
    virtual ~KwSongdbVersionItem();

    /*
     * Accessors
     */

    /// Get the song version.
    KwSongdbVersion* version();

    /// Get the version name.
    QString versionName() const;

    /// Get the name of the writer.
    QString writer() const;

    /// Get the copyright notice.
    QString copyright() const;

    /// Get the lyrics markup.
    QString lyricsMarkup() const;

    /// Get the list of song book number items.
    QList<KwSongdbSongBookSongItem*> songBookNumbers();

  public slots:

    /*
     * Modifier slots
     */

    /// Save the changes to the version object.
    void save(KwSongdbSong* song);

    /// Set the version name.
    void setVersionName(const QString& name);

    /// Set the name of the writer.
    void setWriter(const QString& writer);

    /// Set the copyright notice.
    void setCopyright(const QString& copyright);

    /// Set the lyrics markup.
    void setLyricsMarkup(const QString& lyricsMarkup);

  private:

    /*
     * Variables
     */

    /// Original database version object.
    KwSongdbVersion* m_version;

    /// Version name.
    QString m_name;

    /// Writer.
    QString m_writer;

    /// Copyright.
    QString m_copyright;

    /// Lyrics markup.
    QString m_lyricsMarkup;

    /// Song book numbers.
    QList<KwSongdbSongBookSongItem*> m_songBookNumbers;

};

#endif // _KwSongdbVersionItem_h_

