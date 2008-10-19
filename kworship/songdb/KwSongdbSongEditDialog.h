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

#ifndef _KwSongdbSongEditDialog_h_
#define _KwSongdbSongEditDialog_h_

/**
 * @file KwSongdbSongEditDialog.h
 * @brief Dialog for editing a song.
 * @author James Hogan <james@albanarts.com>
 */

#include <KDialog>

class KwSongdbSongEditWidget;

/** Dialog for editing a song.
 * Allows editing of song information, song versions and lyrics.
 */
class KwSongdbSongEditDialog : public KDialog
{
    Q_OBJECT

  public:

    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwSongdbSongEditDialog();

    /// Destructor.
    virtual ~KwSongdbSongEditDialog();

  private:

    /*
     * Variables
     */

    /// Main widget in dialog.
    KwSongdbSongEditWidget* m_view;
};

#endif // _KwSongdbSongEditDialog_h_
