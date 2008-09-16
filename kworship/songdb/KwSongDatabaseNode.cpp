/**
 * @file KwSongDatabaseNode.cpp
 * @brief A node on a song database tree.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongDatabaseNode.h"

#include <cassert>

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwSongDatabaseNode::KwSongDatabaseNode(KwSongDatabaseNode* parent)
: m_parent(parent)
{
}

/// Destructor.
KwSongDatabaseNode::~KwSongDatabaseNode()
{
}

/*
 * Main interface
 */

/// Get the parent.
KwSongDatabaseNode* KwSongDatabaseNode::getParent()
{
  return m_parent;
}

/// Get data associated with the node.
QVariant KwSongDatabaseNode::getData(int role, int column)
{
  Q_UNUSED(role)
  Q_UNUSED(column)
  return QVariant();
}

/// Get the number of children.
int KwSongDatabaseNode::getChildCount() const
{
  return 0;
}

/// Get a child node by index.
KwSongDatabaseNode* KwSongDatabaseNode::getChild(int index)
{
  assert(index < getChildCount());
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

/// Get the index of a certain child.
int KwSongDatabaseNode::getChildIndex(KwSongDatabaseNode* node) const
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

/// Activate the node using a display manager.
void KwSongDatabaseNode::activate(KwDisplayManager*)
{
}

/// Get a child node by index.
KwSongDatabaseNode* KwSongDatabaseNode::_getChild(int index)
{
  Q_UNUSED(index)
  return 0;
}

