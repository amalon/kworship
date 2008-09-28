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
#include "UpKpr1Presentation.h"

#include <QTemporaryFile>

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpKpr1Slide::UpKpr1Slide(UpKpr1Presentation* presentation, const UpKpr1SlideDcop& dcop, int index)
: UpSlide(presentation)
, m_presentation(presentation)
, m_dcop(dcop)
, m_index(index)
, m_title()
, m_outline()
, m_preview()
{
}

/// Destructor.
UpKpr1Slide::~UpKpr1Slide()
{
}

/*
 * Main interface
 */

QString UpKpr1Slide::title()
{
  if (m_title.isNull())
  {
    m_title = m_dcop.title();
  }
  return m_title;
}

QString UpKpr1Slide::outline()
{
  if (m_outline.isNull())
  {
    m_outline = m_dcop.textObjectsContents().join("\n");
  }
  return m_outline;
}

QString UpKpr1Slide::notes()
{
  return QString();
}

QPixmap UpKpr1Slide::preview()
{
  if (m_preview.isNull())
  {
    UpKpr1Dcop view = m_presentation->dcop().view();
    if (view.isValid())
    {
      QTemporaryFile previewFile;
      previewFile.open();

      bool error;
      QString page;
      page.setNum(m_index+1);
      view.eval(&error, QStringList() << "exportPage(int,int,int,QString,QString,int,int)"
                                      << page                      // Page number
                                      << "1024"                     // Width
                                      << "768"                     // Height
                                      << previewFile.fileName() // Filename
                                      << "PPM"                     // Format
                                      << "50"                      // Quality
                                      << "0"                       // Verbose
                                      );

      if (!error)
      {
        m_preview.load(previewFile.fileName());
        m_preview = m_preview.scaledToHeight(125, Qt::SmoothTransformation);
      }
    }
  }
  return m_preview;
}

#include "UpKpr1Slide.moc"

