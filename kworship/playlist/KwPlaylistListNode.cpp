/**
 * @file KwPlaylistListNode.cpp
 * @brief A playlist node for a list.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistListNode.h"
#include "KwPlaylistList.h"

#include <cassert>

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistListNode::KwPlaylistListNode(KwPlaylistList* item)
: KwPlaylistNode()
, m_item(item)
{
}

/// Destructor.
KwPlaylistListNode::~KwPlaylistListNode()
{
}

/*
 * Main interface
 */

QVariant KwPlaylistListNode::getData(int role, int column)
{
  if (role == Qt::DisplayRole)
  {
    if (column == 0)
    {
      return "List";
    }
  }
  return QVariant();
}

int KwPlaylistListNode::getChildCount() const
{
  return m_item->getItemCount();
}

KwPlaylistNode* KwPlaylistListNode::getChild(int index)
{
  KwPlaylistItem* item = m_item->getItem(index);
  assert(item != 0);
  return item->getNode();
}

