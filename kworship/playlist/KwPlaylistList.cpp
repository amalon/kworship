/**
 * @file KwPlaylistList.cpp
 * @brief A list of playlist items.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistList.h"
#include "KwPlaylistListNode.h"

/*
 * Constructors + destructor.
 */

/// Default constructor.
KwPlaylistList::KwPlaylistList()
: KwPlaylistItem()
, m_playlist()
{
}

/// Destructor.
KwPlaylistList::~KwPlaylistList()
{
}

/*
 * Child management.
 */

/// Add a child.
void KwPlaylistList::addItem(KwPlaylistItem* item)
{
  m_playlist.push_back(item);
}

/// Get the number of children.
int KwPlaylistList::getItemCount() const
{
  return m_playlist.size();
}

/// Get a specific child.
KwPlaylistItem* KwPlaylistList::getItem(int index)
{
  Playlist::iterator it = m_playlist.begin();
  while (index && it != m_playlist.end())
  {
    ++it;
    --index;
  }
  if (it == m_playlist.end())
  {
    return 0;
  }
  else
  {
    return *it;
  }
}

/*
 * Main interface.
 */

KwPlaylistNode* KwPlaylistList::getNode()
{
  return new KwPlaylistListNode(this);
}

