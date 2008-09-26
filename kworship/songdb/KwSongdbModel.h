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

#ifndef _KwSongdbModel_h_
#define _KwSongdbModel_h_

/**
 * @file KwSongdbModel.h
 * @brief A Qt model for songs in the database.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbNode.h"

#include "NodeBasedModel.h"

/// A Qt model for playlist items.
class KwSongdbModel : public NodeBasedModel<KwSongdbNode>
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Default constructor.
    KwSongdbModel(QObject* parent = 0);

    /// Destructor.
    virtual ~KwSongdbModel();

    /*
     * Drag and drop
     */
    Qt::ItemFlags flags(const QModelIndex& index) const;
    QMimeData* mimeData(const QModelIndexList& indexes) const;
};

#endif // _KwSongdbModel_h_

