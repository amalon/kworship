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
 * @file KwDisplayMixer.cpp
 * @brief Mixer of displays.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwDisplayMixer.h"

#include "compiler.h"

#include <cassert>

/*
 * Constructors + destructors
 */

/// Default constructor.
KwDisplayMixer::KwDisplayMixer()
: KwAbstractDisplay()
, m_firstDisplay(0)
{
}

/// Destructor.
KwDisplayMixer::~KwDisplayMixer()
{
  while (m_firstDisplay != 0)
  {
    ProxyDisplay* current = m_firstDisplay;
    m_firstDisplay = current->getNext();
    delete current;
  }
}

/*
 * Main interface.
 */

/// Add display to end of list.
void KwDisplayMixer::attachDisplayToTop(KwAbstractDisplay* display)
{
  ProxyDisplay* proxy;
  if (0 == m_firstDisplay)
  {
    proxy = new ProxyDisplay(this, 0, 0);
    m_firstDisplay = proxy;
  }
  else
  {
    ProxyDisplay* last = m_firstDisplay->getLast();
    proxy = new ProxyDisplay(this, 0, last->getFirstLayerIndex() + last->getLayerCount());
    last->setNext(proxy);
  }
  display->attachChild(proxy);
}

/*
 * ProxyDisplay Constructors + destructors
 */

/// Default constructor.
KwDisplayMixer::ProxyDisplay::ProxyDisplay(KwDisplayMixer* mixer, ProxyDisplay* next, unsigned int firstLayer)
: KwAbstractDisplay()
, m_mixer(mixer)
, m_next(next)
, m_firstLayer(firstLayer)
{
  /// @pre (@p next != 0) => (@p firstLayer == @p next->m_firstLayer)
  assert(0 == next || firstLayer == next->m_firstLayer);
}

/// Destructor.
KwDisplayMixer::ProxyDisplay::~ProxyDisplay()
{
  ProxyDisplay::clearLayersEvent();
}


/*
 * ProxyDisplay Mutators
 */

/// Set the next display.
void KwDisplayMixer::ProxyDisplay::setNext(ProxyDisplay* next)
{
  m_next = next;
}

/*
 * ProxyDisplay Accessors
 */

/// Get the next proxy.
KwDisplayMixer::ProxyDisplay* KwDisplayMixer::ProxyDisplay::getNext() 
{
  return m_next;
}

/// Get the last proxy.
KwDisplayMixer::ProxyDisplay* KwDisplayMixer::ProxyDisplay::getLast()
{
  ProxyDisplay* result = this;
  while (result->m_next != 0)
  {
    result = result->m_next;
  }
  return result;
}

/// Get the index of the first layer.
unsigned int KwDisplayMixer::ProxyDisplay::getFirstLayerIndex() const
{
  return m_firstLayer;
}

/// Get number of layers in this display.
unsigned int KwDisplayMixer::ProxyDisplay::getLayerCount() const
{
  return getCachedLayerCount();
}

/*
 * ProxyDisplay Main interface events for extension
 */

void KwDisplayMixer::ProxyDisplay::setDisplayResolutionEvent(QSize size)
{
  /// @todo How do we handle this, they mustn't conflict!
  Q_UNUSED(size)
}

void KwDisplayMixer::ProxyDisplay::clearLayersEvent()
{
  unsigned int numLayers = getCachedLayerCount();
  if (numLayers > 0)
  {
    adjustLayerCount(-numLayers);
    do
    {
      m_mixer->removeLayer(m_firstLayer);
      --numLayers;
    }
    while (numLayers > 0);
  }
}

void KwDisplayMixer::ProxyDisplay::setLayerEvent(unsigned int index, const KwAbstractLayer* layer, bool insert)
{
  if (insert)
  {
    const unsigned int numLayers = getCachedLayerCount();
    unsigned int insertions = 1;
    if (unlikely(index > numLayers))
    {
      insertions = numLayers - index; 
      const unsigned int startLayer = m_firstLayer + numLayers;
      for (unsigned int i = 0; i < insertions; ++i)
      {
        m_mixer->setLayer(startLayer + i, 0, true);
      }
      ++insertions;
    }
    adjustLayerCount(insertions);
  }
  m_mixer->setLayer(m_firstLayer + index, layer, insert);
}

void KwDisplayMixer::ProxyDisplay::removeLayerEvent(unsigned int index)
{
  m_mixer->removeLayer(m_firstLayer + index);
  adjustLayerCount(-1);
}

/*
 * ProxyDisplay Helper functions
 */

/// Adjust the layer count of layer proxy displays in the list.
void KwDisplayMixer::ProxyDisplay::adjustLayerCount(int adjustment)
{
  /// @pre @p adjustment != 0
  assert(adjustment != 0);
  ProxyDisplay* it = m_next;
  while (it != 0)
  {
    it->m_firstLayer += adjustment;
    it = it->m_next;
  }
}

