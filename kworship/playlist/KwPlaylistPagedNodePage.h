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

#ifndef _KwPlaylistPagedNodePage_h_
#define _KwPlaylistPagedNodePage_h_

/**
 * @file KwPlaylistPagedNodePage.h
 * @brief A playlist node for a page of a paged text item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistNode.h"

class KwPlaylistPaged;

/// A playlist node for a page of a paged text item.
class KwPlaylistPagedNodePage : public KwPlaylistNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistPagedNodePage(KwPlaylistNode* parent, KwPlaylistPaged* item, unsigned int page);

    /// Destructor.
    virtual ~KwPlaylistPagedNodePage();

    /*
     * Main interface
     */

    virtual QVariant getData(int role, int column);

    virtual void activate(KwDisplayManager* manager);

  private:

    /*
     * Variables
     */

    /// Playlist item.
    KwPlaylistPaged* m_item;

    /// Page number.
    unsigned int m_page;
};

#endif // _KwPlaylistPagedNodePage_h_

