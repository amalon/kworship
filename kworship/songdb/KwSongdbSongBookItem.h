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

#ifndef _KwSongdbSongBookItem_h_
#define _KwSongdbSongBookItem_h_

/**
 * @file KwSongdbSongBookItem.h
 * @brief A list widget item for a song book.
 * @author James Hogan <james@albanarts.com>
 */

#include <QObject>
#include <QListWidgetItem>
#include <QString>

class KwSongdbSongBook;

/// A list widget item for a song book.
class KwSongdbSongBookItem : public QObject, public QListWidgetItem
{
    Q_OBJECT

  public:

    /*
     * Constructors + destructor
     */

    /// Construct a new song book.
    KwSongdbSongBookItem(QListWidget* parent = 0);

    /// Construct from an existing song book.
    KwSongdbSongBookItem(KwSongdbSongBook* songBook, QListWidget* parent = 0);

    /// Destructor.
    virtual ~KwSongdbSongBookItem();

    /*
     * Accessors
     */

    /// Get the song book.
    KwSongdbSongBook* songBook();

    /// Get the abreviation text.
    QString abreviation() const;

    /// Get the song book name.
    QString name() const;

    /// Get the description.
    QString description() const;

  public slots:

    /*
     * Modifier slots
     */

    /// Save the changes to the song book object.
    void save();

    /// Set the abreviation text.
    void setAbreviation(const QString& abreviation);

    /// Set the song book name.
    void setName(const QString& name);

    /// Set the description.
    void setDescription(const QString& description);

    /// Update the text.
    void updateText();

  private:

    /*
     * Variables
     */

    /// Original database song book object.
    KwSongdbSongBook* m_songBook;

    /// Short abreviation text.
    QString m_abreviation;

    /// SongBook name.
    QString m_name;

    /// Description.
    QString m_description;

};

#endif // _KwSongdbSongBookItem_h_

