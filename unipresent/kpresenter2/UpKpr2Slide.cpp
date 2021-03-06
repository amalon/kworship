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
 * @file UpKpr2Slide.cpp
 * @brief KPresenter 2 presentation slide.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpKpr2Slide.h"
#include "UpKpr2Presentation.h"

#include <KLocale>

#include <QTemporaryFile>
#include <QDBusReply>
#include <QTextDocument>

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpKpr2Slide::UpKpr2Slide(UpKpr2Presentation* presentation, int index)
: UpSlide(presentation)
, m_presentation(presentation)
, m_index(index)
, m_title()
, m_outline()
, m_notesHtml()
, m_preview()
{
}

/// Destructor.
UpKpr2Slide::~UpKpr2Slide()
{
}

/*
 * Main interface
 */

QString UpKpr2Slide::title()
{
  if (m_title.isNull())
  {
    QDBusInterface* view = m_presentation->dbusView();
    if (0 != view)
    {
      m_title = (QDBusReply<QString>)view->call("pageName", m_index);
    }
  }
  if (m_title.isEmpty())
  {
    return i18n("Page %1", m_index + 1);
  }
  else
  {
    return m_title;
  }
}

QString UpKpr2Slide::outline()
{
  return QString();
}

bool UpKpr2Slide::writeNotes(QTextDocument* doc)
{
  if (m_notesHtml.isNull())
  {
    QDBusInterface* view = m_presentation->dbusView();
    if (0 != view)
    {
      m_notesHtml = (QDBusReply<QString>)view->call("pageNotes", m_index, "html");
    }
    else
    {
      return UpSlide::writeNotes(doc);
    }
  }
  doc->setHtml(m_notesHtml);
  return true;
}

QPixmap UpKpr2Slide::preview()
{
  if (m_preview.isNull())
  {
    QDBusInterface* view = m_presentation->dbusView();
    if (view)
    {
      QTemporaryFile previewFile;
      previewFile.open();

      QDBusMessage result = view->call(
          "exportPageThumbnail",
          m_index,    // page
          167, 125, // size
          previewFile.fileName(), // filename
          "PPM",    // format
          -1        // quality
      );
      if (QDBusMessage::ReplyMessage == result.type())
      {
        if (result.arguments().first().toBool())
        {
          m_preview.load(previewFile.fileName());
        }
      }
    }
  }
  return m_preview;
}

#include "UpKpr2Slide.moc"

