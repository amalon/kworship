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
 * @file KwPlaylistUnknown.cpp
 * @brief Placeholder for an unknown playlist item (forwards compatilibity).
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistUnknown.h"
#include "KwPlaylistUnknownNode.h"

/*
 * Constructors + destructor.
 */

/// Construct from a DOM element.
KwPlaylistUnknown::KwPlaylistUnknown(const QDomElement& element, KwResourceManager* resourceManager)
: KwPlaylistItem(element, resourceManager)
{
  // Do nothing, the dom will be preserved by KwPlaylistItem
  m_type = element.attribute("type");
}

/// Destructor.
KwPlaylistUnknown::~KwPlaylistUnknown()
{
}

/*
 * DOM Translation.
 */

QString KwPlaylistUnknown::itemType() const
{
  return m_type;
}

void KwPlaylistUnknown::exportDetailsToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const
{
  Q_UNUSED(document);
  Q_UNUSED(element);
  Q_UNUSED(resourceManager);
  // Do nothing, the preserved dom will be restored by KwPlaylistItem
}

/*
 * Main interface.
 */

KwPlaylistNode* KwPlaylistUnknown::getNode(KwPlaylistNode* parent)
{
  return new KwPlaylistUnknownNode(parent, this);
}

