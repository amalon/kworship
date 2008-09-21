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

#ifndef _KwSongdbNode_h_
#define _KwSongdbNode_h_

/**
 * @file KwSongdbNode.h
 * @brief A node on a song database tree.
 * @author James Hogan <james@albanarts.com>
 */

#include <QVariant>
#include <QVector>

class KwDisplayManager;

/// A node on a song database tree.
/**
 * Inherit from this class for each song database node type.
 */
class KwSongdbNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwSongdbNode(KwSongdbNode* parent);

    /// Destructor.
    virtual ~KwSongdbNode();

    /*
     * Main interface
     */

    /// Get the parent.
    KwSongdbNode* getParent();

    /// Get a child node by index.
    KwSongdbNode* getChild(int index);

    /// Get the index of a certain child.
    int getChildIndex(KwSongdbNode* node) const;

    /// Get data associated with the node.
    virtual QVariant getData(int role, int column);

    /// Get the number of children.
    virtual int getChildCount() const;

    /// Get flags for this item.
    virtual Qt::ItemFlags getFlags(Qt::ItemFlags defaultFlags) const;

    /// Get mime data string for this set of songs.
    virtual QString mimeData();

  protected:

    /// Get a child node by index.
    virtual KwSongdbNode* _getChild(int index);

  private:

    /*
     * Variables
     */

    /// Parent node.
    KwSongdbNode* m_parent;

    /// Child nodes.
    QVector<KwSongdbNode*> m_children;
};

#endif // _KwSongdbNode_h_

