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

#include <QStackedLayout>
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
KwTextLayer::KwTextLayer(QString text)
: KwAbstractLayer()
, m_style()
, m_text(text)
{
}

/// Destructor.
KwTextLayer::~KwTextLayer()
{
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

void* KwTextLayer::addWidgets(QWidget* master) const
{
  KwTextLayerData* data = new KwTextLayerData;

  data->textBrowser = new QTextBrowser();
  data->textBrowser->setFrameShape(QFrame::NoFrame);
  data->textBrowser->setFrameShadow(QFrame::Plain);
  data->textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  data->textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  data->textBrowser->viewport()->setAutoFillBackground(false);
  {
    QTextCursor cursor = data->textBrowser->textCursor();
    QTextCharFormat fmt;
    fmt.setFontPointSize(64);

#if 0
    QLinearGradient gradient(0, 0, 500, 500);
    gradient.setColorAt(0, Qt::red);
    gradient.setColorAt(1, Qt::green);
#endif

    fmt.setForeground(QBrush(Qt::yellow));
    fmt.setTextOutline(QPen(Qt::blue, 3));

    cursor.insertText(m_text, fmt);
  }

  QStackedLayout* layout = new QStackedLayout();
  layout->setStackingMode(QStackedLayout::StackAll);
  master->setLayout(layout);
  layout->addWidget(data->textBrowser);


  return (void*)data;
}

void KwTextLayer::removeWidgets(QWidget* master, void* rawData) const
{
  Q_UNUSED(master)

  KwTextLayerData* data = reinterpret_cast<KwTextLayerData*>(rawData);

  delete data;
}

