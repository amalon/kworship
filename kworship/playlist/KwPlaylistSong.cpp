/**
 * @file KwPlaylistSong.cpp
 * @brief A song from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistSong.h"
#include "KwSongdb.h"

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistSong::KwPlaylistSong(int versionId)
: KwPlaylistPaged()
, m_version(KwSongdb::self()->getSongVersionById(versionId))
{
}

/// Destructor.
KwPlaylistSong::~KwPlaylistSong()
{
}

