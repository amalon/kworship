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
 * @file KwPlaylistText.cpp
 * @brief A plain text playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistText.h"
#include "KwPlaylistTextNode.h"

/*
 * Constructors + destructor.
 */

/// Default constructor.
KwPlaylistText::KwPlaylistText(const QString& label, const QStringList& blocks)
: KwPlaylistPaged()
, m_label(label)
{
  setTextBlocks(blocks);
}

/// Destructor.
KwPlaylistText::~KwPlaylistText()
{
}

/*
 * Main interface
 */

/// Get the label.
QString KwPlaylistText::getLabel() const
{
  return m_label;
}

KwPlaylistNode* KwPlaylistText::getNode(KwPlaylistNode* parent)
{
  return new KwPlaylistTextNode(parent, this);
}

