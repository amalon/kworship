/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   KWorship is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   KWorship is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with KWorship.  If not, see <http://www.gnu.org/licenses/>.     *
 ***************************************************************************/

#ifndef _KwPlaylistNote_h_
#define _KwPlaylistNote_h_

/**
 * @file KwPlaylistNote.h
 * @brief A plain text playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistItem.h"

#include <QString>

/// A plain text playlist item.
class KwPlaylistNote : public KwPlaylistItem
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistNote(QString content);

    /// Destructor.
    virtual ~KwPlaylistNote();

    /*
     * Main interface.
     */

    /// Get the text.
    QString getContent() const;

    virtual KwPlaylistNode* getNode(KwPlaylistNode* parent);

  private:

    /*
     * Variables
     */

    /// Text in the note.
    QString m_content;
};

#endif // _KwPlaylistNote_h_

