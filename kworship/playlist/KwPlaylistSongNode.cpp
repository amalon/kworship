/**
 * @file KwPlaylistSongNode.cpp
 * @brief A playlist node for a song.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistSongNode.h"
#include "KwPlaylistSongNodeVerse.h"
#include "KwPlaylistSong.h"
#include "KwSongdbVersion.h"
#include "KwSongdbSong.h"

#include <KIcon>

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistSongNode::KwPlaylistSongNode(KwPlaylistNode* parent, KwPlaylistSong* item)
: KwPlaylistNode(parent)
, m_item(item)
{
}

/// Destructor.
KwPlaylistSongNode::~KwPlaylistSongNode()
{
}

/*
 * Main interface
 */

QVariant KwPlaylistSongNode::getData(int role, int column)
{
  if (role == Qt::DisplayRole)
  {
    if (column == 0)
    {
      return m_item->getSongVersion()->getSong()->getName();
    }
  }
  else if (role == Qt::DecorationRole)
  {
    if (column == 0)
    {
      return KIcon("song");
    }
  }
  return QVariant();
}

int KwPlaylistSongNode::getChildCount() const
{
  return m_item->getSongVersion()->getNumLyricsOrders();
}

KwPlaylistNode* KwPlaylistSongNode::_getChild(int index)
{
  return new KwPlaylistSongNodeVerse(this, m_item, index);
}

