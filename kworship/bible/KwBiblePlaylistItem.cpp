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
 * @file KwBiblePlaylistItem.cpp
 * @brief A playlist item for bible passages.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBiblePlaylistItem.h"
#include "KwBiblePlaylistItemNode.h"

KW_REGISTER_PLAYLIST_ITEM(KwBiblePlaylistItem, "bible")

/*
 * Constructors + destructor.
 */

/// Construct from reference information.
KwBiblePlaylistItem::KwBiblePlaylistItem(KwBibleModule* module, const KwBibleModule::Key& moduleKey)
: KwPlaylistItem()
, m_passage()
{
  module->fillPassage(moduleKey, &m_passage);
}

/// Construct from a DOM element.
KwBiblePlaylistItem::KwBiblePlaylistItem(const QDomElement& element, KwResourceManager* resourceManager)
: KwPlaylistItem()
{
  /// @todo Implement bible passage import.
}

/// Destructor.
KwBiblePlaylistItem::~KwBiblePlaylistItem()
{
}

/*
 * DOM Translation.
 */

QString KwBiblePlaylistItem::itemType() const
{
  return "bible";
}

void KwBiblePlaylistItem::exportDetailsToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const
{
  /// @todo Implement bible passage export.
}

/*
 * Main interface
 */

KwPlaylistNode* KwBiblePlaylistItem::getNode(KwPlaylistNode* parent)
{
  return new KwBiblePlaylistItemNode(parent, this);
}

/*
 * Accessors
 */

/// Get the bible passage.
const KwBiblePassage& KwBiblePlaylistItem::passage() const
{
  return m_passage;
}

