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
 * @file KwLocalDisplay.cpp
 * @brief Local controller of displays.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwLocalDisplay.h"

#include <QPainter>
#include <QPaintEvent>
#include <QStackedLayout>

/*
 * Constructors + destructors
 */

/// Primary constructor.
KwLocalDisplay::KwLocalDisplay(QWidget* parent)
: QWidget(parent)
, KwAbstractDisplay()
, m_isPrimary(false)
, m_layout(new QStackedLayout)
{
  m_layout->setStackingMode(QStackedLayout::StackAll);
  setLayout(m_layout);
}

/// Destructor.
KwLocalDisplay::~KwLocalDisplay()
{
  delete m_layout;
}

/*
 * Public methods
 */

/// Set whether this display is the primary display.
void KwLocalDisplay::setPrimary(bool newIsPrimary)
{
  m_isPrimary = newIsPrimary;
  resizeEvent(0);
  if (newIsPrimary)
  {
    setCursor(Qt::BlankCursor);
  }
  else
  {
    setCursor(Qt::ArrowCursor);
  }
}

/*
 * QT Events
 */

void KwLocalDisplay::paintEvent(QPaintEvent *e)
{
  QPainter painter(this);
  painter.setClipRegion(e->region());
  painter.setBrush(QBrush(Qt::black));
  painter.setPen(QPen(Qt::black));
  painter.drawRect(e->rect());
}

void KwLocalDisplay::resizeEvent(QResizeEvent*)
{
  if (m_isPrimary)
  {
    getHighestParent()->setDisplayResolution(size());
  }
}

void KwLocalDisplay::closeEvent(QCloseEvent*)
{
  closed();
}

/*
 * Main interface events for extension
 */

void KwLocalDisplay::setDisplayResolutionEvent(QSize size)
{
  // Make this widget the right size
  resize(size);
}
#define IND 1
void KwLocalDisplay::clearLayersEvent()
{
  LayerData::iterator it;
  unsigned int index = 0;
  while (m_layerWidgetData.end() != (it = m_layerWidgetData.begin()))
  {
    getCachedLayer(index)->removeWidgets(m_layout->widget(0), *it);
    m_layout->removeWidget(m_layout->widget(0));
    ++index;
  }
  m_layerWidgetData.clear();
  m_layout->setCurrentIndex(IND);
}

void KwLocalDisplay::setLayerEvent(unsigned int index, const KwAbstractLayer* layer, bool insert)
{
  QWidget* newWidget = new QWidget;
  if (index < m_layerWidgetData.size() && !insert)
  {
    removeLayerEvent(index);
  }
  m_layout->insertWidget(index, newWidget);
  void* data = layer->addWidgets(newWidget);
  m_layerWidgetData.set(index, data, insert);
  m_layout->setCurrentIndex(IND);
}

void KwLocalDisplay::removeLayerEvent(unsigned int index)
{
  LayerData::iterator it = m_layerWidgetData.getLayerIterator(index, false);
  assert(it != m_layerWidgetData.end());
  getCachedLayer(index)->removeWidgets(m_layout->widget(index), *it);
  m_layerWidgetData.erase(it);
  m_layout->removeWidget(m_layout->widget(index));
  m_layout->setCurrentIndex(IND);
}

