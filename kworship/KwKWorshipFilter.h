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

#ifndef _KwKWorshipFilter_h_
#define _KwKWorshipFilter_h_

/**
 * @file KwKWorshipFilter.h
 * @brief Main KWorship archive load and save filter.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwLoadSaveFilter.h"

/// Main KWorship archive load and save filter.
class KwKWorshipFilter : public KwLoadSaveFilter
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwKWorshipFilter();

    /// Destructor.
    virtual ~KwKWorshipFilter();

    /*
     * Main interface
     */
    
    /// Reimplemented.
    virtual KwDocument* load(const KUrl& url, const QString& mimeType);

    /// Reimplemented.
    virtual bool save(KwDocument* doc, const KUrl& url, const QString& mimeType);

  protected:

    /*
     * Virtual interface
     */

    /// Reimplemented.
    virtual void v_saveLimitations(KwDocument* doc, const QString& mimeType, Limitations* o_limitations);
};

#endif // _KwKWorshipFilter_h_
