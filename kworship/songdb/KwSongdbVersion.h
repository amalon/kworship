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

#ifndef _KwSongdbVersion_h_
#define _KwSongdbVersion_h_

/**
 * @file KwSongdbVersion.h
 * @brief A song version from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbLyrics.h"

#include <kdemacros.h>

#include <QHash>
#include <QVector>

class KwSongdbSong;
class KwSongdbSongBookSong;

/// A song version from the database.
class KDE_EXPORT KwSongdbVersion
{
  public:

    /*
     * Types
     */

    /// Version data fields.
    enum Field
    {
      Name = 0x1,
      Writer = 0x2,
      Copyright = 0x4,
      Lyrics = 0x8
    };
    Q_DECLARE_FLAGS(Fields, Field)

    /*
     * Constructors + destructor
     */

    /** Construct a new version for database insertion.
     * This constructs a blank song version which will be inserted into the
     * database when it is saved.
     * @param song The song for the version to belong to.
     */
    KwSongdbVersion(KwSongdbSong* song);

    /** Construct from the database.
     * Loads the version information from the database.
     * @param id Database id of version.
     */
    KwSongdbVersion(int id);

    /// Destructor.
    virtual ~KwSongdbVersion();

    /*
     * Accessors
     */

    /// Get the version id.
    int id();

    /// Get the song this is a version of.
    KwSongdbSong* song();

    /// Get the name of this version.
    QString name() const;

    /** Get a non-empty name of this version.
     * @return The name or i18n("Default version").
     */
    QString niceName() const;

    /// Get the name of the writer.
    QString writer() const;

    /// Get the copyright notice.
    QString copyright() const;

    /// Get the lyrics.
    const KwSongdbLyrics& lyrics() const;

    /// Get song book numbers.
    QList<KwSongdbSongBookSong*> songBookNumbers();

    /*
     * Mutators
     */

    /// Set the name.
    void setName(const QString& name);

    /// Set the writer.
    void setWriter(const QString& writer);

    /// Set the copyright notice.
    void setCopyright(const QString& copyright);

    /// Set the lyrics markup.
    void setLyricsMarkup(const QString& markup);

    /// Set the lyrics plain text verses.
    void setLyricsPlainVerses(const QStringList& plainVerses);

    /// Set the lyrics.
    void setLyrics(const KwSongdbLyrics& lyrics);

    /// Save changes to the version data.
    void save();

  private:

    /*
     * Variables
     */

    /// Version id.
    int m_id;

    /// Song object.
    KwSongdbSong* m_song;

    /// Which fields have been modified.
    Fields m_modifiedFields;

    /// Name of this version.
    QString m_name;

    /// Name of the writer.
    QString m_writer;

    /// Copyright notice.
    QString m_copyright;

    /// Lyrics.
    KwSongdbLyrics m_lyrics;

    /// Whether song book numbers have been loaded.
    bool m_songBookNumbersLoaded;

    /// Song book numbers.
    QList<KwSongdbSongBookSong*> m_songBookNumbers;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(KwSongdbVersion::Fields)

#endif // _KwSongdbVersion_h_

