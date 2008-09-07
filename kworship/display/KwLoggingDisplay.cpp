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

