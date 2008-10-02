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

#ifndef _KwSongdbVersionNode_h_
#define _KwSongdbVersionNode_h_

/**
 * @file KwSongdbVersionNode.h
 * @brief A node for a song version.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbNode.h"

#include <QIcon>

/// A node for filtering songs.
class KwSongdbVersionNode : public KwSongdbNode
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwSongdbVersionNode(KwSongdbNode* parent, QString label, int id);

    /// Destructor.
    virtual ~KwSongdbVersionNode();

    /*
     * Main interface
     */

    /// Get data associated with the node.
    virtual QVariant getData(int role, int column);

    /// Get flags for this item.
    virtual Qt::ItemFlags getFlags(Qt::ItemFlags defaultFlags) const;

    /// Get mime data string for this set of songs.
    virtual QString mimeData();

    /// Override the icon to display.
    void setIcon(const QIcon& icon);

  private:

    /*
     * Variables
     */

    /// Label.
    QString m_label;

    /// Version id.
    int m_id;

    /// Icon.
    QIcon m_icon;
};

#endif // _KwSongdbNode_h_

