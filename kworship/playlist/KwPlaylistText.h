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

#ifndef _KwPlaylistText_h_
#define _KwPlaylistText_h_

/**
 * @file KwPlaylistText.h
 * @brief A plain text playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistPaged.h"

#include <KwExport.h>

/// A plain text playlist item.
class KWMAIN_EXPORT KwPlaylistText : public KwPlaylistPaged
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Default constructor.
    KwPlaylistText(const QString& label, const QStringList& blocks);

    /// Destructor.
    virtual ~KwPlaylistText();

    /*
     * DOM Translation.
     */

    virtual QString itemType() const;
    virtual void exportDetailsToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const;

    /*
     * Main interface
     */

    /// Get the label.
    QString getLabel() const;

    virtual KwPlaylistNode* getNode(KwPlaylistNode* parent);

  private:
    
    /*
     * Variables
     */

    /// Label.
    QString m_label;
};

#endif // _KwPlaylistText_h_

