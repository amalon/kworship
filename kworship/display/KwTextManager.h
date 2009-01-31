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

#ifndef _KwTextManager_h_
#define _KwTextManager_h_

/**
 * @file KwTextManager.h
 * @brief Text manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractDisplayManager.h"

#include <kdemacros.h>

#include <QString>

class KwCssScope;
class KwTextLayer;

/// Text manager.
/**
 * High level interface for controlling text on screen.
 */
class KDE_EXPORT KwTextManager : public KwAbstractDisplayManager
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwTextManager();

    /// Destructor.
    virtual ~KwTextManager();

    /*
     * Main interface
     */

    /// Apply the styles in a scope.
    void applyStyles(KwCssScope* scope);

    /// Clear all text.
    void clear();

    /// Set the text.
    void setText(const QString& text);

    /// Set formatted text.
    void setHtml(const QString& html);

  private:

    /*
     * Variables
     */

    /// Current text layer.
    KwTextLayer* m_currentLayer;
};

#endif // _KwTextManager_h_

