/**
 * @file KwPlaylistSongNodeVerse.cpp
 * @brief A playlist node for a song verse.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistSongNodeVerse.h"
#include "KwPlaylistSong.h"
#include "KwSongdbVersion.h"
#include "KwSongdbLyrics.h"
#include "KwDisplayManager.h"

#include <KIcon>

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistSongNodeVerse::KwPlaylistSongNodeVerse(KwPlaylistNode* parent, KwPlaylistSong* item, int verse)
: KwPlaylistNode(parent)
, m_item(item)
, m_verse(verse)
{
}

/// Destructor.
KwPlaylistSongNodeVerse::~KwPlaylistSongNodeVerse()
{
}

/*
 * Main interface
 */

QVariant KwPlaylistSongNodeVerse::getData(int role, int column)
{
  if (role == Qt::DisplayRole)
  {
    if (column == 0)
    {
      return m_item->getSongVersion()->getLyricsByOrder(m_verse)->getLyrics();
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

void KwPlaylistSongNodeVerse::activate(KwDisplayManager* manager)
{
  manager->applyStyles(m_item);
  // Set text
  manager->text.setText(m_item->getSongVersion()->getLyricsByOrder(m_verse)->getLyrics());
}

