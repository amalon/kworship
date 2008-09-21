/***************************************************************************
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   This file is part of KWorship.                                        *
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

#ifndef _KwDisplayMixer_h_
#define _KwDisplayMixer_h_

/**
 * @file KwDisplayMixer.h
 * @brief Mixer of displays.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractDisplay.h"

/// Mixer of displays.
/**
 * Manages multiple layers of displays and mixing of layers.
 */
class KwDisplayMixer : public KwAbstractDisplay
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwDisplayMixer();

    /// Destructor.
    virtual ~KwDisplayMixer();

    /*
     * Main interface.
     */

    /// Add display to end of list.
    void attachDisplayToTop(KwAbstractDisplay* display);

  private:

    /*
     * Types
     */

    class ProxyDisplay;

    /*
     * Variables
     */

    /// First item on the list of display proxies.
    ProxyDisplay* m_firstDisplay;

};

/// Proxy display for translating display commands onto main display.
class KwDisplayMixer::ProxyDisplay : public KwAbstractDisplay
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    ProxyDisplay(KwDisplayMixer* mixer, ProxyDisplay* next, unsigned int firstLayer);

    /// Destructor.
    virtual ~ProxyDisplay();

    /*
     * Mutators
     */

    /// Set the next display.
    void setNext(ProxyDisplay* next);

    /*
     * Accessors
     */

    /// Get the next proxy.
    ProxyDisplay* getNext();

    /// Get the last proxy.
    ProxyDisplay* getLast();

    /// Get the index of the first layer.
    unsigned int getFirstLayerIndex() const;

    /// Get number of layers in this display.
    unsigned int getLayerCount() const;

  protected:

    /*
     * Main interface events for extension
     */

    virtual void setDisplayResolutionEvent(QSize size);

    virtual void clearLayersEvent();

    virtual void setLayerEvent(unsigned int index, const KwAbstractLayer* layer, bool insert);

    virtual void removeLayerEvent(unsigned int index);

  private:

    /*
     * Variables
     */

    /// Mixer display.
    KwDisplayMixer* m_mixer;

    /// The next proxy display.
    ProxyDisplay* m_next;

    /// First layer number.
    unsigned int m_firstLayer;

    /*
     * Helper functions
     */

    /// Adjust the layer count of layer proxy displays in the list.
    void adjustLayerCount(int adjustment);
};

#endif // _KwDisplayMixer_h_

