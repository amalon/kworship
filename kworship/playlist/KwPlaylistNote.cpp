/**
 * @file KwPlaylistNote.cpp
 * @brief A plain text playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistNote.h"
#include "KwPlaylistNoteNode.h"

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistNote::KwPlaylistNote(QString content)
: KwPlaylistItem()
, m_content(content)
{
}

/// Destructor.
KwPlaylistNote::~KwPlaylistNote()
{
}

/*
 * Main interface.
 */

/// Get the text.
QString KwPlaylistNote::getContent() const
{
  return m_content;
}

KwPlaylistNode* KwPlaylistNote::getNode()
{
  return new KwPlaylistNoteNode(this);
}

