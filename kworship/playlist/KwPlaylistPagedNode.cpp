/**
 * @file KwPlaylistPagedNode.cpp
 * @brief A playlist node for a text.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistPaged.h"
#include "KwPlaylistPagedNode.h"
#include "KwPlaylistPagedNodePage.h"

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistPagedNode::KwPlaylistPagedNode(KwPlaylistNode* parent, KwPlaylistPaged* item)
: KwPlaylistNode(parent)
, m_item(item)
{
}

/// Destructor.
KwPlaylistPagedNode::~KwPlaylistPagedNode()
{
}

/*
 * Main interface
 */

int KwPlaylistPagedNode::getChildCount() const
{
  return m_item->getPageCount();
}

KwPlaylistNode* KwPlaylistPagedNode::_getChild(int index)
{
  return new KwPlaylistPagedNodePage(this, m_item, index);
}

