/**
 * @file KwSongdbLyricsOrder.cpp
 * @brief An order item for a song from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbLyricsOrder.h"

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwSongdbLyricsOrder::KwSongdbLyricsOrder(int order, KwSongdbLyrics* lyrics)
: m_order(order)
, m_lyrics(lyrics)
{
}

/// Destructor.
KwSongdbLyricsOrder::~KwSongdbLyricsOrder()
{
}

/*
 * Accessors
 */

/// Get the order.
int KwSongdbLyricsOrder::getOrder() const
{
  return m_order;
}

/// Get the lyrics object.
KwSongdbLyrics* KwSongdbLyricsOrder::getLyrics() const
{
  return m_lyrics;
}

