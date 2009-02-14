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

#ifndef _KwFilter_h_
#define _KwFilter_h_

/**
 * @file KwFilter.h
 * @brief Abstract file filter.
 * @author James Hogan <james@albanarts.com>
 */

#include <kdemacros.h>

#include <QString>

/// Export file filter.
class KDE_EXPORT KwFilter
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwFilter();

    /// Destructor.
    virtual ~KwFilter();

    /*
     * Main interface
     */
    
    /// Get the name of the file format.
    const QString& formatName() const;

  private:

    /*
     * Variables
     */

    /// Name of the file format.
    QString m_formatName;
};

#endif // _KwFilter_h_
