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

#ifndef _repeatMacros_h_
#define _repeatMacros_h_

#define MACRO_COMMA ,
#define MACRO_NOTHING

// Top level

#define REPEAT_0(X, SEP)
#define REPEAT_1(X, SEP)  X(0)
#define REPEAT_2(X, SEP)  X(0) SEP X(1)
#define REPEAT_3(X, SEP)  X(0) SEP X(1) SEP X(2)
#define REPEAT_4(X, SEP)  X(0) SEP X(1) SEP X(2) SEP X(3)
#define REPEAT_5(X, SEP)  X(0) SEP X(1) SEP X(2) SEP X(3) SEP X(4)
#define REPEAT_6(X, SEP)  X(0) SEP X(1) SEP X(2) SEP X(3) SEP X(4) SEP X(5)
#define REPEAT_7(X, SEP)  X(0) SEP X(1) SEP X(2) SEP X(3) SEP X(4) SEP X(5) SEP X(6)
#define REPEAT_8(X, SEP)  X(0) SEP X(1) SEP X(2) SEP X(3) SEP X(4) SEP X(5) SEP X(6) SEP X(7)

#define REPEAT(X,N)       REPEAT_##N(X, MACRO_NOTHING)
#define REPEAT_LIST(X,N)  REPEAT_##N(X, MACRO_COMMA)

// First level

#define REPEATA_0(X, B, SEP)
#define REPEATA_1(X, B, SEP)      X(B, 0)
#define REPEATA_2(X, B, SEP)      X(B, 0) SEP X(B, 1)
#define REPEATA_3(X, B, SEP)      X(B, 0) SEP X(B, 1) SEP X(B, 2)
#define REPEATA_4(X, B, SEP)      X(B, 0) SEP X(B, 1) SEP X(B, 2) SEP X(B, 3)
#define REPEATA_5(X, B, SEP)      X(B, 0) SEP X(B, 1) SEP X(B, 2) SEP X(B, 3) SEP X(B, 4)
#define REPEATA_6(X, B, SEP)      X(B, 0) SEP X(B, 1) SEP X(B, 2) SEP X(B, 3) SEP X(B, 4) SEP X(B, 5)
#define REPEATA_7(X, B, SEP)      X(B, 0) SEP X(B, 1) SEP X(B, 2) SEP X(B, 3) SEP X(B, 4) SEP X(B, 5) SEP X(B, 6)
#define REPEATA_8(X, B, SEP)      X(B, 0) SEP X(B, 1) SEP X(B, 2) SEP X(B, 3) SEP X(B, 4) SEP X(B, 5) SEP X(B, 6) SEP X(B, 7)

#define REPEATA(X,B,N)       REPEATA_##N(X, B, MACRO_NOTHING)
#define REPEATA_LIST(X,B,N)  REPEATA_##N(X, B, MACRO_COMMA)

// Second level

#define REPEATB_0(X, B, C, SEP)
#define REPEATB_1(X, B, C, SEP)      X(B, C, 0)
#define REPEATB_2(X, B, C, SEP)      X(B, C, 0) SEP X(B, C, 1)
#define REPEATB_3(X, B, C, SEP)      X(B, C, 0) SEP X(B, C, 1) SEP X(B, C, 2)
#define REPEATB_4(X, B, C, SEP)      X(B, C, 0) SEP X(B, C, 1) SEP X(B, C, 2) SEP X(B, C, 3)
#define REPEATB_5(X, B, C, SEP)      X(B, C, 0) SEP X(B, C, 1) SEP X(B, C, 2) SEP X(B, C, 3) SEP X(B, C, 4)
#define REPEATB_6(X, B, C, SEP)      X(B, C, 0) SEP X(B, C, 1) SEP X(B, C, 2) SEP X(B, C, 3) SEP X(B, C, 4) SEP X(B, C, 5)
#define REPEATB_7(X, B, C, SEP)      X(B, C, 0) SEP X(B, C, 1) SEP X(B, C, 2) SEP X(B, C, 3) SEP X(B, C, 4) SEP X(B, C, 5) SEP X(B, C, 6)
#define REPEATB_8(X, B, C, SEP)      X(B, C, 0) SEP X(B, C, 1) SEP X(B, C, 2) SEP X(B, C, 3) SEP X(B, C, 4) SEP X(B, C, 5) SEP X(B, C, 6) SEP X(B, C, 7)

#define REPEATB(X,B,C,N)       REPEATB_##N(X, B, C, MACRO_NOTHING)
#define REPEATB_LIST(X,B,C,N)  REPEATB_##N(X, B, C, MACRO_COMMA)

#endif // _repeatMacros_h_

