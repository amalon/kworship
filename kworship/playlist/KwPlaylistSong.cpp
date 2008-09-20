/**
 * @file KwPlaylistSong.cpp
 * @brief A song from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistSong.h"
#include "KwPlaylistSongNode.h"
#include "KwSongdb.h"

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistSong::KwPlaylistSong(KwSongdbVersion* version)
: KwPlaylistItem()
, m_version(version)
{
}

/// Destructor.
KwPlaylistSong::~KwPlaylistSong()
{
}

/*
 * Accessors
 */

/// Get the song version object.
KwSongdbVersion* KwPlaylistSong::getSongVersion()
{
  return m_version;
}

/*
 * Main interface
 */

KwPlaylistNode* KwPlaylistSong::getNode(KwPlaylistNode* parent)
{
  return new KwPlaylistSongNode(parent, this);
}

