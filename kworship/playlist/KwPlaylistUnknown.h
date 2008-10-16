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

#ifndef _KwPlaylistUnknown_h_
#define _KwPlaylistUnknown_h_

/**
 * @file KwPlaylistUnknown.h
 * @brief Placeholder for an unknown playlist item (forwards compatilibity).
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistItem.h"

#include <QString>

/// Placeholder for an unknown playlist item (forwards compatilibity).
class KwPlaylistUnknown : public KwPlaylistItem
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Construct from a DOM element.
    KwPlaylistUnknown(const QDomElement& element, KwResourceManager* resourceManager);

    /// Destructor.
    virtual ~KwPlaylistUnknown();

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
     * Variables
     */

    /// Type of item.
    QString m_type;

};

#endif // _KwPlaylistUnknown_h_

