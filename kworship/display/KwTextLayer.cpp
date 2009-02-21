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
 * @file KwTextLayer.cpp
 * @brief Layer of pretty text.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwTextLayer.h"

#include <QGridLayout>
#include <QSpacerItem>
#include <QTextBrowser>

/*
 * Constructors + destructors
 */

/// Default constructor.
KwTextLayer::KwTextLayer()
: KwAbstractLayer()
, m_style()
, m_text()
{
}

/// Primaryt constructor.
KwTextLayer::KwTextLayer(QString text, bool formatted)
: KwAbstractLayer()
, m_style()
, m_text(text)
, m_formatted(formatted)
{
}

/// Destructor.
KwTextLayer::~KwTextLayer()
{
}

/*
 * Mutators
 */

/// Set text styles.
void KwTextLayer::setStyle(const KwTextStyle& style)
{
  m_style = style;
}

/*
 * Private structures
 */

struct KwTextLayerData
{
  QTextBrowser* textBrowser;
};

/*
 * Methods
 */

#include <QtDebug>
void* KwTextLayer::addWidgets(QWidget* master) const
{
  KwTextLayerData* data = new KwTextLayerData;

  data->textBrowser = new QTextBrowser();
  data->textBrowser->setFrameShape(QFrame::NoFrame);
  data->textBrowser->setFrameShadow(QFrame::Plain);
  data->textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  data->textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  data->textBrowser->viewport()->setAutoFillBackground(false);

  // Set the content
  QFont font = m_style.character.font;
  data->textBrowser->document()->setDefaultFont(font);
  if (m_formatted)
  {
    data->textBrowser->setHtml(m_text);
  }
  else
  {
    data->textBrowser->setText(m_text);
  }

  // Select the content
  QTextCursor cursor = data->textBrowser->textCursor();
  cursor.select(QTextCursor::Document);

  // Create a text character format with outline etc and apply
  QTextCharFormat fmt;
  fmt.setForeground(m_style.character.brush);
  if (m_style.character.outline.enabled)
  {
    fmt.setTextOutline(m_style.character.outline.pen);
  }
  cursor.mergeCharFormat(fmt);

  // Slightly hacky way of getting margins
  QGridLayout* layout = new QGridLayout();
  master->setLayout(layout);
  layout->addWidget(data->textBrowser, 1, 1, 1, 1);
  layout->addItem(new QSpacerItem(1, m_style.layout.margins.top * master->height(),
                  QSizePolicy::Fixed, QSizePolicy::Fixed), 0, 1);
  layout->addItem(new QSpacerItem(m_style.layout.margins.left * master->width(), 1,
                  QSizePolicy::Fixed, QSizePolicy::Fixed), 1, 0);
  layout->addItem(new QSpacerItem(m_style.layout.margins.right * master->width(), 1,
                  QSizePolicy::Fixed, QSizePolicy::Fixed), 1, 2);
  layout->addItem(new QSpacerItem(1, m_style.layout.margins.bottom * master->height(),
                  QSizePolicy::Fixed, QSizePolicy::Fixed), 2, 1);

  return (void*)data;
}

void KwTextLayer::removeWidgets(QWidget* master, void* rawData) const
{
  Q_UNUSED(master)

  KwTextLayerData* data = reinterpret_cast<KwTextLayerData*>(rawData);

  delete data;
}

