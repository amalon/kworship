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
 * @file UpOoSlide.cpp
 * @brief OpenOffice.org presentation slide.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpOoSlide.h"

#include <com/sun/star/drawing/XShapes.hpp>
#include <com/sun/star/text/XText.hpp>

#include <cassert>

using namespace com::sun::star::drawing;
using namespace com::sun::star::text;
using namespace com::sun::star::uno;

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpOoSlide::UpOoSlide(uno::XInterface* interface, QObject* parent)
: UpSlide(parent)
, m_interface(interface)
{
}

/// Destructor.
UpOoSlide::~UpOoSlide()
{
}

/*
 * Main interface
 */

QString UpOoSlide::title()
{
  return UpSlide::title();
}

QString UpOoSlide::outline()
{
  QStringList result;
  // Go through the shapes
  Reference<XShapes> shapes(m_interface, UNO_QUERY);
  int numShapes = shapes->getCount();
  for (int i = 0; i < numShapes; ++i)
  {
    Reference<XText> shape;
    shapes->getByIndex(i) >>= shape;
    if (0 != shape.get())
    {
      QString text = QString::fromUtf16((const sal_Unicode*)shape->getString());
      result << text;
    }
  }
  return result.join("\n");
}

QString UpOoSlide::notes()
{
  return QString();
}

QPixmap UpOoSlide::preview()
{
  return QPixmap();
}

#include "UpOoSlide.moc"

