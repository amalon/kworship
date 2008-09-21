/***************************************************************************
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   This file is part of KWorship.                                        *
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

#include <QAbstractItemModel>

class KwSongdbNode;

/// A Qt model for playlist items.
class KwSongdbModel : public QAbstractItemModel
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
     * Main interface
     */

    /// Set the root node.
    void setRootNode(KwSongdbNode* root);
    KwSongdbNode* itemFromIndex(const QModelIndex &index) const;

    QModelIndex index(int row, int column, const QModelIndex& parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    // Drag and drop
    Qt::ItemFlags flags(const QModelIndex& index) const;
    QMimeData* mimeData(const QModelIndexList& indexes) const;

  private:

    /*
     * Variables
     */

    /// Root item.
    KwSongdbNode* m_root;
};

#endif // _KwSongdbModel_h_

