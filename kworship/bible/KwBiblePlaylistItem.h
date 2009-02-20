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

#ifndef _KwBiblePlaylistItem_h_
#define _KwBiblePlaylistItem_h_

/**
 * @file KwBiblePlaylistItem.h
 * @brief A playlist item for bible passages.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBibleModule.h"
#include "KwBiblePassage.h"

#include <KwPlaylistItem.h>

#include <kdemacros.h>

#include <QString>

class KwBibleManager;

/// A playlist item for bible passages.
class KDE_EXPORT KwBiblePlaylistItem : public KwPlaylistItem
{
    KW_PLAYLIST_ITEM
    KW_CSS_SCOPE("bible")

  public:
    
    /*
     * Constructors + destructor.
     */

    /** Construct from reference information.
     * @param module Bible module.
     * @param moduleKey Bible passage key.
     */
    KwBiblePlaylistItem(KwBibleModule* module, const KwBibleModule::Key& moduleKey);

    /// Construct from a DOM element.
    KwBiblePlaylistItem(const QDomElement& element, KwResourceManager* resourceManager);

    /// Destructor.
    virtual ~KwBiblePlaylistItem();

    /*
     * DOM Translation.
     */

    // Reimplemented
    virtual QString itemType() const;

    // Reimplemented
    virtual void exportDetailsToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const;

    /*
     * Main interface
     */

    virtual KwPlaylistNode* getNode(KwPlaylistNode* parent);

    /*
     * Accessors
     */

    /// Get the bible passage.
    const KwBiblePassage& passage() const;

  private:

    /*
     * Variables
     */

    /// The bible passage.
    KwBiblePassage m_passage;
};

#endif // _KwBiblePlaylistItem_h_

