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

#include <QAbstractItemModel>

class KwPlaylistNode;

/// A Qt model for playlist items.
class KwPlaylistModel : public QAbstractItemModel
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
     * Main interface
     */

    /// Set the root node.
    void setRootNode(KwPlaylistNode* root);
    KwPlaylistNode* itemFromIndex(const QModelIndex &index) const;

    QModelIndex index(int row, int column, const QModelIndex& parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    // Drag and drop
    QStringList mimeTypes() const;
    Qt::DropActions supportedDropActions() const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
    bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent);

  private:

    /*
     * Variables
     */

    /// Root item.
    KwPlaylistNode* m_root;
};

#endif // _KwPlaylistModel_h_

