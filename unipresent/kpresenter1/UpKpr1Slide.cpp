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
 * @file UpKpr1Slide.cpp
 * @brief KPresenter 1 presentation slide.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpKpr1Slide.h"

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpKpr1Slide::UpKpr1Slide(const UpKpr1SlideDcop& dcop, QObject* parent)
: UpSlide(parent)
, m_dcop(dcop)
{
}

/// Destructor.
UpKpr1Slide::~UpKpr1Slide()
{
}

/*
 * Main interface
 */

QString UpKpr1Slide::outline()
{
  return "outline";
}

QString UpKpr1Slide::notes()
{
  return "notes";
}

QPixmap UpKpr1Slide::preview()
{
  return QPixmap();
}

#include "UpKpr1Slide.moc"

