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
 * @file KwImportFilter.cpp
 * @brief Import file filter.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwImportFilter.h"

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwImportFilter::KwImportFilter()
: KwFilter()
, m_importMimeTypes()
{
}

/// Destructor.
KwImportFilter::~KwImportFilter()
{
}

/*
 * Accessors
 */

/// Get a list of importable mime types.
QStringList KwImportFilter::importMimeTypes() const
{
  return m_importMimeTypes;
}
