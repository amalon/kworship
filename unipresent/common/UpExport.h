/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2009 James Hogan <james@albanarts.com>                      *
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

#ifndef _UpExport_h_
#define _UpExport_h_

/**
 * @file UpExport.h
 * @brief Define export macros for unipresent.
 * @author James Hogan <james@albanarts.com>
 */

#include <kdemacros.h>

#if defined(MAKE_UNIPRESENT_LIB)
  // Building library
  #define UNIPRESENT_EXPORT KDE_EXPORT
#else
  // Using library
  #define UNIPRESENT_EXPORT KDE_IMPORT
#endif

#endif // _UpExport_h_
