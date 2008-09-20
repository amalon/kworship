/**
 * @file KwSongdbLyrics.cpp
 * @brief A verse of lyrics from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbLyrics.h"

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwSongdbLyrics::KwSongdbLyrics(int id, const QString& lyrics)
: m_id(id)
, m_lyrics(lyrics)
{
}

/// Destructor.
KwSongdbLyrics::~KwSongdbLyrics()
{
}

/*
 * Accessors
 */

/// Get lyrics id.
int KwSongdbLyrics::getId() const
{
  return m_id;
}

/// Get the lyrics.
QString KwSongdbLyrics::getLyrics() const
{
  return m_lyrics;
}

