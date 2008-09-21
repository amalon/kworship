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
 * @file KwLoggingDisplay.cpp
 * @brief Logging controller of displays.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwLoggingDisplay.h"

#include <QtDebug>

/*
 * Constructors + destructors
 */

/// Default constructor.
KwLoggingDisplay::KwLoggingDisplay()
: KwAbstractDisplay()
{
}

/// Destructor.
KwLoggingDisplay::~KwLoggingDisplay()
{
}

/*
 * Main interface events for extension
 */

void KwLoggingDisplay::setDisplayResolutionEvent(QSize size)
{
  qDebug() << __FUNCTION__ << "(" << size << ")";
}

void KwLoggingDisplay::clearLayersEvent()
{
  qDebug() << __FUNCTION__ << "(" << ")";
  m_layerWidgetData.clear();
}

void KwLoggingDisplay::setLayerEvent(unsigned int index, const KwAbstractLayer* layer, bool insert)
{
  qDebug() << __FUNCTION__ << "(" << index << "," << (void*)layer << "," << (insert ? "insert" : "replace") << ")";
  m_layerWidgetData.set(index, 0, insert);
}

void KwLoggingDisplay::removeLayerEvent(unsigned int index)
{
  qDebug() << __FUNCTION__ << "(" << index << ")";
  LayerData::iterator it = m_layerWidgetData.getLayerIterator(index, false);
  assert(it != m_layerWidgetData.end());
  m_layerWidgetData.erase(it);
}

