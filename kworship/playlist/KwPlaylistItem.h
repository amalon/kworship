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

#ifndef _KwPlaylistItem_h_
#define _KwPlaylistItem_h_

/**
 * @file KwPlaylistItem.h
 * @brief An item that can be added to a playlist.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssScope.h"

#include <QString>

class KwResourceManager;
class KwPlaylistNode;

class QDomDocument;
class QDomElement;

/// An item that can be added to a playlist.
/**
 * Inherit from this class for each playlist item type.
 */
class KwPlaylistItem : public KwCssScope
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Default constructor.
    KwPlaylistItem();

    /// Destructor.
    virtual ~KwPlaylistItem();

    /*
     * DOM Translation.
     */

    /// Export this item to the DOM.
    void exportToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const;

    /// Get the type of the item.
    virtual QString itemType() const = 0;

    /// Export details of this item to the DOM.
    virtual void exportDetailsToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const = 0;

    /*
     * Main interface.
     */

    /// Get a tree node for this item.
    virtual KwPlaylistNode* getNode(KwPlaylistNode* parent) = 0;
};

#endif // _KwPlaylistItem_h_

