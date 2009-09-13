/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008-2009 James Hogan <james@albanarts.com>                 *
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
 * @file UpOkSlide.cpp
 * @brief Okular presentation slide.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpOkSlide.h"
#include "UpOkPresentation.h"

#include <KLocale>
#include <KIcon>

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpOkSlide::UpOkSlide(UpOkPresentation* presentation, int index)
: UpSlide(presentation)
, m_presentation(presentation)
, m_index(index)
{
}

/// Destructor.
UpOkSlide::~UpOkSlide()
{
}

/*
 * Main interface
 */

QString UpOkSlide::title()
{
  return i18n("Page %1", m_index + 1);
}

QString UpOkSlide::outline()
{
  return QString();
}

bool UpOkSlide::writeNotes(QTextDocument* doc)
{
  return false;
}

QPixmap UpOkSlide::preview()
{
  return KIcon("okular").pixmap(45,30);
}

#include "UpOkSlide.moc"

