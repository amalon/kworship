/**
 * @file KwPlaylistNoteNode.cpp
 * @brief A playlist node for a note.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistNoteNode.h"
#include "KwPlaylistNote.h"

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistNoteNode::KwPlaylistNoteNode(KwPlaylistNote* item)
: KwPlaylistNode()
, m_item(item)
{
}

/// Destructor.
KwPlaylistNoteNode::~KwPlaylistNoteNode()
{
}

/*
 * Main interface
 */

QVariant KwPlaylistNoteNode::getData(int role, int column)
{
  if (role == Qt::DisplayRole)
  {
    if (column == 0)
    {
      return m_item->getContent();
    }
  }
  return QVariant();
}

