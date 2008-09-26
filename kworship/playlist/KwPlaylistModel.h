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

#ifndef _KwPlaylistModel_h_
#define _KwPlaylistModel_h_

/**
 * @file KwPlaylistModel.h
 * @brief A Qt model for playlist items.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistNode.h"

#include "NodeBasedModel.h"

/// A Qt model for playlist items.
class KwPlaylistModel : public NodeBasedModel<KwPlaylistNode>
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Default constructor.
    KwPlaylistModel(QObject* parent = 0);

    /// Destructor.
    virtual ~KwPlaylistModel();

    /*
     * Drag and drop
     */

    QStringList mimeTypes() const;
    Qt::DropActions supportedDropActions() const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
    bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent);

};

#endif // _KwPlaylistModel_h_

