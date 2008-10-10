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

#ifndef _NodeBasedModel_h_
#define _NodeBasedModel_h_

/**
 * @file NodeBasedModel.h
 * @brief A Qt model based on nodes.
 * @author James Hogan <james@albanarts.com>
 */

#include "compiler.h"

#include <QAbstractItemModel>
#include <QVector>
#include <QVariant>

#include <cassert>

/// A node in the model.
class DefaultModelNode
{
  public:

    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    DefaultModelNode(DefaultModelNode* parent)
    : m_parent(parent)
    , m_children()
    {
    }

    /// Destructor.
    virtual ~DefaultModelNode()
    {
    }

    /*
     * Main interface
     */

    /// Get the parent.
    DefaultModelNode* getParent()
    {
      return m_parent;
    }

    /// Get a child node by index.
    DefaultModelNode* getChild(int index)
    {
      if (unlikely(index >= getChildCount()))
      {
        return 0;
      }

      if (index >= m_children.size())
      {
        int prevSize = m_children.size();
        int newSize = getChildCount();
        m_children.resize(newSize);
        for (int i = prevSize; i < newSize; ++i)
        {
          m_children[i] = 0;
        }
      }
      if (0 == m_children[index])
      {
        m_children[index] = _getChild(index);
      }
      return m_children[index];
    }

    /// Notify that children have been added.
    void childrenAdded(int first, int last)
    {
      if (first > m_children.size())
      {
        first = m_children.size();
      }
      m_children.insert(first, last - first + 1, 0);
    }

    /// Notify that children have been removed.
    void childrenRemoved(int first, int last)
    {
      int cacheSize = m_children.size();
      if (first < cacheSize)
      {
        if (last >= cacheSize)
        {
          last = cacheSize - 1;
        }
        for (int i = first; i <= last; ++i)
        {
          delete m_children[i];
        }
        m_children.remove(first, last - first + 1);
      }
    }

    /// Clear the cache of child nodes.
    void clearChildCache()
    {
      foreach (DefaultModelNode* node, m_children)
      {
        delete node;
      }
      m_children.clear();
    }

    /// Get the index of a certain child.
    int getChildIndex(DefaultModelNode* node) const
    {
      for (int i = 0; i < m_children.size(); ++i)
      {
        if (m_children[i] == node)
        {
          return i;
        }
      }
      return -1;
    }

    /// Get data associated with the node.
    virtual QVariant getData(int role, int column)
    {
      Q_UNUSED(role)
      Q_UNUSED(column)
      return QVariant();
    }

    /// Get the number of children.
    virtual int getChildCount() const
    {
      return 0;
    }

  protected:

    /// Get a child node by index.
    virtual DefaultModelNode* _getChild(int index)
    {
      Q_UNUSED(index)
      return 0;
    }

  private:

    /*
     * Variables
     */

    /// Parent node.
    DefaultModelNode* m_parent;

    /// Child nodes.
    QVector<DefaultModelNode*> m_children;

};


/// A Qt model based on nodes.
template <class NODE = DefaultModelNode>
class NodeBasedModel : public QAbstractItemModel
{
  public:

    /*
     * Types
     */

    /// Node type.
    typedef NODE Node;

    /*
     * Constructors + destructor.
     */

    /// Default constructor.
    NodeBasedModel(QObject* parent = 0)
    : QAbstractItemModel(parent)
    , m_root(0)
    {
    }

    /// Destructor.
    virtual ~NodeBasedModel()
    {
      delete m_root;
    }

    /*
     * Main interface
     */

    /// Set the root node.
    void setRootNode(Node* root)
    {
      delete m_root;
      m_root = root;
      reset();
    }
    Node* itemFromIndex(const QModelIndex &index) const
    {
      if (index.isValid())
      {
        return reinterpret_cast<Node*>(index.internalPointer());
      }
      else
      {
        return m_root;
      }
    }

    QModelIndex index(int row, int column, const QModelIndex& parent) const
    {
      if (0 == m_root)
      {
        return QModelIndex();
      }
      Node* parentNode = itemFromIndex(parent);
      assert(0 != parentNode);
      return createIndex(row, column, parentNode->getChild(row));
    }

    QModelIndex parent(const QModelIndex &child) const
    {
      Node* node = itemFromIndex(child);
      assert(0 != node);
      DefaultModelNode* parentNode = node->getParent();
      if (0 == parentNode)
      {
        return QModelIndex();
      }
      DefaultModelNode* grandParentNode = parentNode->getParent();
      if (0 == grandParentNode)
      {
        return QModelIndex();
      }
      int row = grandParentNode->getChildIndex(parentNode);
      assert(row != -1);
      return createIndex(row, child.column(), parentNode);
    }
    int rowCount(const QModelIndex &parent) const
    {
      Node* parentNode = itemFromIndex(parent);
      if (0 == parentNode)
      {
        return 0;
      }
      return parentNode->getChildCount();
    }
    virtual int columnCount(const QModelIndex &parent) const
    {
      Q_UNUSED(parent)
      return 1;
    }
    QVariant data(const QModelIndex &index, int role) const
    {
      Node* item = itemFromIndex(index);
      if (0 == item)
      {
        return QVariant();
      }
      return item->getData(role, index.column());
    }
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const
    {
      Q_UNUSED(section)
      Q_UNUSED(orientation)
      Q_UNUSED(role)
      return QVariant();
    }

  private:

    /*
     * Variables
     */

    /// Root item.
    Node* m_root;
};

#endif // _NodeBasedModel_h_

