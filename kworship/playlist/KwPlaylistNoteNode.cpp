/**
 * @file KwPlaylistNoteNode.cpp
 * @brief A playlist node for a note.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistNoteNode.h"
#include "KwPlaylistNote.h"

#include <KIcon>

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistNoteNode::KwPlaylistNoteNode(KwPlaylistNode* parent, KwPlaylistNote* item)
: KwPlaylistNode(parent)
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
  else if (role == Qt::DecorationRole)
  {
    if (column == 0)
    {
      return KIcon("note");
    }
  }
  return QVariant();
}

