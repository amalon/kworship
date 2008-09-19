/**
 * @file KwPlaylistListNode.cpp
 * @brief A playlist node for a list.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistListNode.h"
#include "KwPlaylistList.h"

#include <KIcon>

#include <cassert>

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistListNode::KwPlaylistListNode(KwPlaylistNode* parent, KwPlaylistList* item)
: KwPlaylistNode(parent)
, m_item(item)
{
}

/// Destructor.
KwPlaylistListNode::~KwPlaylistListNode()
{
}

/*
 * Accessors
 */

KwPlaylistList* KwPlaylistListNode::getItem()
{
  return m_item;
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
  else if (role == Qt::DecorationRole)
  {
    if (column == 0)
    {
      return KIcon("playlist");
    }
  }
  return QVariant();
}

int KwPlaylistListNode::getChildCount() const
{
  return m_item->getItemCount();
}

KwPlaylistNode* KwPlaylistListNode::_getChild(int index)
{
  KwPlaylistItem* item = m_item->getItem(index);
  assert(item != 0);
  return item->getNode(this);
}

