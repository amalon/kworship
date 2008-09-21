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

#ifndef _KwPlaylistNode_h_
#define _KwPlaylistNode_h_

/**
 * @file KwPlaylistNode.h
 * @brief A node on a playlist tree.
 * @author James Hogan <james@albanarts.com>
 */

#include <QVariant>
#include <QVector>

class KwDisplayManager;

/// A node on a playlist tree.
/**
 * Inherit from this class for each playlist node type.
 */
class KwPlaylistNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistNode(KwPlaylistNode* parent);

    /// Destructor.
    virtual ~KwPlaylistNode();

    /*
     * Main interface
     */

    /// Get the parent.
    KwPlaylistNode* getParent();

    /// Get a child node by index.
    KwPlaylistNode* getChild(int index);

    /// Clear the cache of child nodes.
    void clearChildCache();

    /// Get the index of a certain child.
    int getChildIndex(KwPlaylistNode* node) const;

    /// Get data associated with the node.
    virtual QVariant getData(int role, int column);

    /// Get the number of children.
    virtual int getChildCount() const;

    /// Get the flags for this node.
    virtual Qt::ItemFlags getFlags(Qt::ItemFlags& defaultFlags) const;

    /// Activate the node using a display manager.
    virtual void activate(KwDisplayManager* manager);

  protected:

    /// Get a child node by index.
    virtual KwPlaylistNode* _getChild(int index);

  private:

    /*
     * Variables
     */

    /// Parent node.
    KwPlaylistNode* m_parent;

    /// Child nodes.
    QVector<KwPlaylistNode*> m_children;
};

#endif // _KwPlaylistNode_h_

