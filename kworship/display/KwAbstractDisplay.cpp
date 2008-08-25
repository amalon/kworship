/**
 * @file KwAbstractDisplay.cpp
 * @brief Display interface class.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractDisplay.h"

#include <cassert>

/*
 * Constructors + destructors
 */

/// Default constructor.
KwAbstractDisplay::KwAbstractDisplay()
: m_parent(0)
, m_children()
, m_displayResolution(800,600)
, m_layers()
{
}

/// Destructor.
KwAbstractDisplay::~KwAbstractDisplay()
{
  /// Disconnect each of the children.
  DisplayList::iterator it;
  for (it = m_children.begin(); it != m_children.end(); ++it)
  {
    childDetachedEvent(*it);
    assert((*it)->m_parent == this &&"Child not correctly parented");
    (*it)->m_parent = 0;
    (*it)->disconnectedEvent();
  }

  /// Disconnect from parent.
  if (0 != m_parent)
  {
    m_parent->detachChild(this);
  }
}

/*
 * Heirarchy management
 */

/// Attach a child to this object.
void KwAbstractDisplay::attachChild(KwAbstractDisplay* child)
{
  /// @note Potential MT/Callback issue. child is attached before it is brought up to date so it may need locking.

  // Attach
  assert(0 == child->m_parent);
  child->m_parent = this;
  m_children.push_back(child);

  // Callbacks
  childAttachedEvent(child);
  
  // Bring child up to date
  child->clearLayers();
  child->setDisplayResolution(m_displayResolution);
  LayerList::iterator it;
  unsigned int counter = 0;
  for (it = m_layers.begin(); it != m_layers.end(); ++it)
  {
    child->setLayer(counter, *it, true);
    ++counter;
  }
}

/// Detach a child from this object.
void KwAbstractDisplay::detachChild(KwAbstractDisplay* child)
{
  DisplayList::iterator it;
  it = m_children.begin();
  while (it != m_children.end() && (*it) != child)
  {
    ++it;
  }
  assert(it != m_children.end());
  m_children.erase(it);

  childDetachedEvent(child);
  assert((*it)->m_parent == this &&"Child not correctly parented");
  child->m_parent = 0;
  child->disconnectedEvent();
}

/*
 * Main interface
 *
 * These pretty much just call the equivalent event and pass the command on to
 * the display's children.
 */

/// Set the display resolution.
void KwAbstractDisplay::setDisplayResolution(QSize size)
{
  // Callbacks
  setDisplayResolutionEvent(size);

  // Keep a record
  m_displayResolution = size;

  // Callbacks
  DisplayList::iterator it;
  for (it = m_children.begin(); it != m_children.end(); ++it)
  {
    (*it)->setDisplayResolution(size);
  }
}

/// Clear the layers.
void KwAbstractDisplay::clearLayers()
{
  // Callbacks
  clearLayersEvent();

  // Keep a record
  m_layers.clear();

  // Callbacks
  DisplayList::iterator it;
  for (it = m_children.begin(); it != m_children.end(); ++it)
  {
    (*it)->clearLayers();
  }
}

/// Set the contents of a layer.
void KwAbstractDisplay::setLayer(unsigned int index, const KwAbstractLayer* layer, bool insert)
{
  // Callbacks
  setLayerEvent(index, layer, insert);

  // Keep a record
  m_layers.set(index, layer, insert);

  // Callbacks
  DisplayList::iterator displayIt;
  for (displayIt = m_children.begin(); displayIt != m_children.end(); ++displayIt)
  {
    (*displayIt)->setLayer(index, layer, insert);
  }
}

/// Remove a layer.
void KwAbstractDisplay::KwAbstractDisplay::removeLayer(unsigned int index)
{
  // Callbacks
  removeLayerEvent(index);

  // Keep a record
  m_layers.erase(index);

  // Callbacks
  DisplayList::iterator displayIt;
  for (displayIt = m_children.begin(); displayIt != m_children.end(); ++displayIt)
  {
    (*displayIt)->removeLayer(index);
  }
}

/*
 * Accessors
 */

/// Get the cached display resolution.
QSize KwAbstractDisplay::getDisplayResolution() const
{
  return m_displayResolution;
}

/// Get the highest level parent display.
KwAbstractDisplay* KwAbstractDisplay::getHighestParent()
{
  if (m_parent)
  {
    return m_parent->getHighestParent();
  }
  else
  {
    return this;
  }
}

/*
 * Access to layer data.
 */

/// Get the number of cached layers.
unsigned int KwAbstractDisplay::getCachedLayerCount() const
{
  return m_layers.size();
}

/// Get cached layer.
const KwAbstractLayer* KwAbstractDisplay::getCachedLayer(unsigned int index) const
{
  LayerList::const_iterator it = m_layers.getLayerConstIterator(index);
  assert(it != m_layers.end());
  return *it;
}

