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

#ifndef _KwPlaylistFile_h_
#define _KwPlaylistFile_h_

/**
 * @file KwPlaylistFile.h
 * @brief A file based playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistItem.h"

#include <QUrl>

class KwDisplayManager;

/// A file based playlist item.
class KwPlaylistFile : public KwPlaylistItem
{
    KW_PLAYLIST_ITEM

  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistFile(const QUrl& url);

    /// Construct from a DOM element.
    KwPlaylistFile(const QDomElement& element, KwResourceManager* resourceManager);

    /// Destructor.
    virtual ~KwPlaylistFile();

    /*
     * DOM Translation.
     */

    virtual QString itemType() const;
    virtual void exportDetailsToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const;

    /*
     * Main interface.
     */

    virtual KwPlaylistNode* getNode(KwPlaylistNode* parent);

    /// Activate the file.
    virtual void activate(KwDisplayManager* manager);

    /*
     * Accessors
     */

    /// Get the image url.
    QUrl getUrl() const;

  private:
    
    /*
     * Variables
     */

    /// File url.
    QUrl m_url;
};

#endif // _KwPlaylistFile_h_

