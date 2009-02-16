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

#ifndef _KwPlaylistList_h_
#define _KwPlaylistList_h_

/**
 * @file KwPlaylistList.h
 * @brief A list of playlist items.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistItem.h"

#include <kdemacros.h>

#include <QList>

/// A list of playlist items.
/**
 * Inherit from this class for each playlist item type.
 */
class KDE_EXPORT KwPlaylistList : public KwPlaylistItem
{
    KW_PLAYLIST_ITEM

  public:
    
    /*
     * Constructors + destructor.
     */

    /// Default constructor.
    KwPlaylistList();

    /// Construct from a DOM element.
    KwPlaylistList(const QDomElement& element, KwResourceManager* resourceManager);

    /// Destructor.
    virtual ~KwPlaylistList();

    /*
     * Child management.
     */

    /// Add a child.
    void addItem(KwPlaylistItem* item, int position = -1);

    /// Get the number of children.
    int getItemCount() const;

    /// Get a specific child.
    KwPlaylistItem* getItem(int index);
    /// Get a specific child.
    const KwPlaylistItem* getItem(int index) const;

    /*
     * DOM Translation.
     */

    virtual QString itemType() const;
    virtual void exportDetailsToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const;

    /*
     * Main interface.
     */

    virtual KwPlaylistNode* getNode(KwPlaylistNode* parent);

  private:

    /*
     * Types
     */

    /// List of playlist items.
    typedef QList<KwPlaylistItem*> Playlist;

    /*
     * Variables
     */

    /// The actual playlist.
    Playlist m_playlist;
    
};

#endif // _KwPlaylistList_h_

