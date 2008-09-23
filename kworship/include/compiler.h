/***************************************************************************
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   This file is part of KWorship.                                        *
 *                                                                         *
 *   KWorship is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   KWorship is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with KWorship.  If not, see <http://www.gnu.org/licenses/>.     *
 ***************************************************************************/

#ifndef _compiler_h_
#define _compiler_h_

/**
 * @file compiler.h
 * @brief Generic compiler-specific macros.
 * @author James Hogan <james@albanarts.com>
 */

#ifdef __GNUC__

#define likely(X)    __builtin_expect(!!(X), 1)
#define unlikely(X)  __builtin_expect(!!(X), 0)

#else

#define likely(X)   (X)
#define unlikely(X) (X)

#endif

#endif // _compiler_h_