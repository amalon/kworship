/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   KWorship is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   KWorship is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with KWorship.  If not, write to the Free Software Foundation,  *
 *   Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.   *
 ***************************************************************************/

/**
 * @file KwSongdbLyrics.cpp
 * @brief Contains and manupulates a set of song lyrics.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbLyrics.h"

/*
 * Constructors + destructor
 */

/// Default constructor.
KwSongdbLyrics::KwSongdbLyrics()
: m_markup()
{
}

/// Primary constructor.
KwSongdbLyrics::KwSongdbLyrics(const QString& markup)
: m_markup(markup)
{
}

/// Destructor.
KwSongdbLyrics::~KwSongdbLyrics()
{
}

/*
 * Accessors
 */

/// Get the markup for these lyrics.
QString KwSongdbLyrics::markup() const
{
  return m_markup;
}

/// Get verses of lyrics in plain text.
QStringList KwSongdbLyrics::plainVerses() const
{
  return m_markup.split("\n\n");
}

/*
 * Mutators
 */

/// Set the lyrics from markup.
void KwSongdbLyrics::setMarkup(const QString& markup)
{
  m_markup = markup;
}

/// Set the lyrics from plain text verses.
void KwSongdbLyrics::setPlainVerses(const QStringList& plainVerses)
{
  m_markup = plainVerses.join("\n\n");
}
