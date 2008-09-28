/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
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

/**
 * @file UpKpr1SlideDcop.cpp
 * @brief DCOP interface for a kpresenter slide.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpKpr1SlideDcop.h"

/*
 * Constructors + destructor
 */

/// Default constructor.
UpKpr1SlideDcop::UpKpr1SlideDcop()
: UpKpr1Dcop()
{
}

/// Primary constructor.
UpKpr1SlideDcop::UpKpr1SlideDcop(const UpKpr1Dcop& interface)
: UpKpr1Dcop(interface)
{
}

/// Destructor.
UpKpr1SlideDcop::~UpKpr1SlideDcop()
{
}

/*
 * Main interface
 */

