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

#ifndef _KwImportFilter_h_
#define _KwImportFilter_h_

/**
 * @file KwImportFilter.h
 * @brief Import file filter.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwFilter.h"

#include <kdemacros.h>

#include <QStringList>

class KwDocument;
class KUrl;

/// Import file filter.
class KDE_EXPORT KwImportFilter : public virtual KwFilter
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwImportFilter();

    /// Destructor.
    virtual ~KwImportFilter();

    /*
     * Main interface
     */
    
    /// Load the document from a file.
    virtual KwDocument* load(const KUrl& url) = 0;

    /*
     * Accessors
     */

    /// Get a list of importable mime types.
    QStringList importMimeTypes() const;

  protected:

    /*
     * Variables
     */

    /// List of import mime types.
    QStringList m_importMimeTypes;
};

#endif // _KwImportFilter_h_
