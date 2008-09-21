/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   KWorship is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   KWorship is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with KWorship.  If not, see <http://www.gnu.org/licenses/>.     *
 ***************************************************************************/

/**
 * @file KwPlaylistPagedNodePage.cpp
 * @brief A playlist node for a paged text item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistPagedNodePage.h"
#include "KwPlaylistPaged.h"

#include "KwDisplayManager.h"

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistPagedNodePage::KwPlaylistPagedNodePage(KwPlaylistNode* parent, KwPlaylistPaged* item, unsigned int page)
: KwPlaylistNode(parent)
, m_item(item)
, m_page(page)
{
}

/// Destructor.
KwPlaylistPagedNodePage::~KwPlaylistPagedNodePage()
{
}

/*
 * Main interface
 */

QVariant KwPlaylistPagedNodePage::getData(int role, int column)
{
  if (role == Qt::DisplayRole)
  {
    if (column == 0)
    {
      return m_item->getPageText(m_page);
    }
  }
  return QVariant();
}

void KwPlaylistPagedNodePage::activate(KwDisplayManager* manager)
{
  manager->applyStyles(m_item);
  // Set text
  manager->text.setText(m_item->getPageText(m_page));
}

