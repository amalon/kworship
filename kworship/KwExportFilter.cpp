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

/**
 * @file KwExportFilter.cpp
 * @brief Export file filter.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwExportFilter.h"

/*
 * Limitation Constructors + destructor
 */

/// Default constructor.
KwExportFilter::Limitation::Limitation()
{
}

/// Destructor.
KwExportFilter::Limitation::~Limitation()
{
}

/*
 * Limitations Constructors + destructor
 */

/// Default constructor.
KwExportFilter::Limitations::Limitations()
: m_limitations()
{
}

/// Destructor.
KwExportFilter::Limitations::~Limitations()
{
}

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwExportFilter::KwExportFilter()
: KwFilter()
{
}

/// Destructor.
KwExportFilter::~KwExportFilter()
{
}

/*
 * Main interface
 */

/// Obtain information about any data that can not be saved.
void KwExportFilter::saveLimitations(KwDocument* doc, Limitations* o_limitations)
{
  v_saveLimitations(doc, o_limitations);
}
