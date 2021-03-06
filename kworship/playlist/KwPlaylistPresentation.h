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

#ifndef _KwPlaylistPresentation_h_
#define _KwPlaylistPresentation_h_

/**
 * @file KwPlaylistPresentation.h
 * @brief A presentation document playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistFile.h"

#include <KwExport.h>

/// A presentation document playlist item.
class KWMAIN_EXPORT KwPlaylistPresentation : public KwPlaylistFile
{
    KW_PLAYLIST_ITEM

  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistPresentation(const QUrl& url);

    /// Construct from a DOM element.
    KwPlaylistPresentation(const QDomElement& element, KwResourceManager* resourceManager);

    /// Destructor.
    virtual ~KwPlaylistPresentation();

    /*
     * DOM Translation.
     */

    virtual QString itemType() const;
    virtual void exportDetailsToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const;

    /*
     * Main interface.
     */

    virtual void activate(KwDisplayManager* manager);
};

#endif // _KwPlaylistPresentation_h_

