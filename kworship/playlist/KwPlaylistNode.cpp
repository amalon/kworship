/**
 * @file KwPlaylistNode.cpp
 * @brief A node on a playlist tree.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistNode.h"

/*
 * Constructors + destructor.
 */

/// Default constructor.
KwPlaylistNode::KwPlaylistNode()
{
}

/// Destructor.
KwPlaylistNode::~KwPlaylistNode()
{
}

/*
 * Main interface
 */

/// Get the parent.
KwPlaylistNode* KwPlaylistNode::getParent()
{
  return m_parent;
}

/// Get data associated with the node.
QVariant KwPlaylistNode::getData(int role, int column)
{
  Q_UNUSED(role)
  Q_UNUSED(column)
  return QVariant();
}

/// Get the number of children.
int KwPlaylistNode::getChildCount() const
{
  return 0;
}

/// Get a child node by index.
KwPlaylistNode* KwPlaylistNode::getChild(int index)
{
  Q_UNUSED(index)
  return 0;
}

