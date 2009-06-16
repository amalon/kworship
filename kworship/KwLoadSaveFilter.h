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

#ifndef _KwLoadSaveFilter_h_
#define _KwLoadSaveFilter_h_

/**
 * @file KwLoadSaveFilter.h
 * @brief Load and save file filter.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwImportFilter.h"
#include "KwExportFilter.h"
#include "KwExport.h"

/// Load and save file filter.
/**
 * Load save filters can be included on the list of file formats in
 * save and load as well as in import and export.
 */
class KWMAIN_EXPORT KwLoadSaveFilter : public KwImportFilter, public KwExportFilter
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwLoadSaveFilter();

    /// Destructor.
    virtual ~KwLoadSaveFilter();
};

#endif // _KwLoadSaveFilter_h_
