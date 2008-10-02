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

#ifndef _KwAbstractDisplay_h_
#define _KwAbstractDisplay_h_

/**
 * @file KwAbstractDisplay.h
 * @brief Display interface class.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractLayer.h"
#include "KwLayerData.h"

#include <QSize>
#include <list>

/// Abstract display interface with heirarchy.
/**
 * Interface for controlling a KWorship display object.
 */
class KwAbstractDisplay
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwAbstractDisplay();

    /// Destructor.
    virtual ~KwAbstractDisplay();

    /*
     * Heirarchy management
     */

    /// Attach a child to this object.
    void attachChild(KwAbstractDisplay* child);

    /// Detach a child from this object.
    void detachChild(KwAbstractDisplay* child);

    /*
     * Main interface
     */

    /// Set the display resolution.
    void setDisplayResolution(QSize size);

    /// Clear the layers.
    void clearLayers();

    /// Set the contents of a layer.
    /**
     * @param index  The index to set or insert at.
     * @param layer  The contents of the layer.
     * @param insert When true a new layer with the contents of @p layer is
     *               inserted at position @p index.
     */
    void setLayer(unsigned int index, const KwAbstractLayer* layer, bool insert = false);

    /// Remove a layer.
    /**
     * @param index  The index of the layer to remove.
     */
    void removeLayer(unsigned int index);

    /*
     * Accessors
     */

    /// Get the cached display resolution.
    QSize getDisplayResolution() const;

    /// Get the highest level parent display.
    KwAbstractDisplay* getHighestParent();

  protected:

    /*
     * Types
     */

    /// List of displays.
    typedef std::list<KwAbstractDisplay*> DisplayList;

    /// Layer list.
    typedef KwLayerData<const KwAbstractLayer*> LayerList;

    /*
     * Main interface events for extension
     */

    /// @copydoc setDisplayResolution(QSize)
    virtual void setDisplayResolutionEvent(QSize size)
    {
      Q_UNUSED(size)
    }

    /// @copydoc clearLayers()
    virtual void clearLayersEvent()
    {
    }

    /// @copydoc setLayer(unsigned int, const KwAbstractLayer*, bool)
    virtual void setLayerEvent(unsigned int index, const KwAbstractLayer* layer, bool insert)
    {
      Q_UNUSED(index)
      Q_UNUSED(layer)
      Q_UNUSED(insert)
    }

    /// @copydoc removeLayer(unsigned int)
    virtual void removeLayerEvent(unsigned int index)
    {
      Q_UNUSED(index)
    }

    /*
     * Other events for extension
     */

    /// Called when a child is attached.
    virtual void childAttachedEvent(KwAbstractDisplay* display)
    {
      Q_UNUSED(display)
    }

    /// Called when a child is detatched.
    virtual void childDetachedEvent(KwAbstractDisplay* display)
    {
      Q_UNUSED(display)
    }

    /// Called when we get connected to a parent.
    virtual void connectedEvent()
    {
    }

    /// Called when we get disconnected from a parent.
    virtual void disconnectedEvent()
    {
    }

    /*
     * Access to layer data.
     */

    /// Get the number of cached layers.
    unsigned int getCachedLayerCount() const;

    /// Get cached layer.
    const KwAbstractLayer* getCachedLayer(unsigned int index) const;

  private:

    /*
     * Heirarchical layout variables
     */

    /// Parent display.
    /**
     * This is the display we get commands from.
     */
    KwAbstractDisplay* m_parent;

    /// Set of child displays.
    /**
     * We echo all commands on to these displays.
     */
    DisplayList m_children;

    /*
     * Variables
     */

    /// Display resolution.
    QSize m_displayResolution;

    /// Layers.
    LayerList m_layers;

};

#endif // _KwAbstractDisplay_h_

