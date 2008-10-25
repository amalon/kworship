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

#ifndef _KwSongdbSongBooksEditWidget_h_
#define _KwSongdbSongBooksEditWidget_h_

/**
 * @file KwSongdbSongBooksEditWidget.h
 * @brief Widget for editing song books.
 * @author James Hogan <james@albanarts.com>
 */

#include "ui_KwSongdbSongBooksEditWidget_base.h"

#include <QWidget>

/** Widget for editing song books.
 * Allows editing of song book information.
 */
class KwSongdbSongBooksEditWidget : public QWidget, public Ui::KwSongdbSongBooksEditWidget_base
{
    Q_OBJECT

  public:

    /*
     * Static
     */

    /// Show the edit song books dialog.
    static KwSongdbSongBooksEditWidget* showDialog();

    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwSongdbSongBooksEditWidget();

    /// Destructor.
    virtual ~KwSongdbSongBooksEditWidget();

  public slots:

    /*
     * Saving and loading
     */

    /// Save to database.
    void save();

    /// Add a song book.
    void addSongBook();

  signals:

    /*
     * Signals
     */

    /// Emitted when the changed state of the form changes.
    void changed(bool changed);

  private slots:

    /*
     * Private slots
     */

    /// A different song book has been selected.
    void songBookChanged(QListWidgetItem* current, QListWidgetItem* previous);

    /// Remove the selected song book.
    void removeSongBook();

};

#endif // _KwSongdbSongBooksEditWidget_h_
