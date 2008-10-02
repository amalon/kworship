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

#ifndef _KwLayerData_h_
#define _KwLayerData_h_

/**
 * @file KwLayerData.h
 * @brief Per layer data with display interface.
 * @author James Hogan <james@albanarts.com>
 */

#include <list>
#include <cassert>

/// Layer storage.
template <typename T>
class KwLayerData
{
  private:

    /*
     * Types
     */

    /// List of layers.
    typedef std::list<T> LayerList;

  public:

    /*
     * Types
     */

    /// Type to store.
    typedef T value_type;

    /// Iterator.
    typedef typename LayerList::iterator iterator;

    /// Constant iterator.
    typedef typename LayerList::const_iterator const_iterator;

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwLayerData()
    {
    }

    /// Destructor.
    ~KwLayerData()
    {
    }

    /*
     * Main interface
     */

    /// Get the number of layers.
    unsigned int size() const
    {
      return m_layers.size();
    }

    /// Clear the layers.
    void clear()
    {
      m_layers.clear();
    }

    /// Set the contents of a layer.
    /**
     * @param index  The index to set or insert at.
     * @param data   The data to set.
     * @param insert When true a new layer with the contents of @p layer is
     *               inserted at position @p index.
     */
    void set(unsigned int index, const value_type& data, bool insert)
    {
      typename LayerList::iterator layerIt = getLayerIterator(index, insert);
      /// @pre !insert => m_layers[index] must exist
      assert(layerIt != m_layers.end());
      *layerIt = data;
    }

    /// Remove a layer by iterator.
    /**
     * @param it  The iterator for the layer to remove.
     */
    void erase(iterator it)
    {
      m_layers.erase(it);
    }

    /// Remove a layer by index.
    /**
     * @param index  The index of the layer to remove.
     */
    void erase(unsigned int index)
    {
      typename LayerList::iterator layerIt = getLayerIterator(index, false);
      /// @pre m_layers[index] must exist
      assert(layerIt != m_layers.end());
      m_layers.erase(layerIt);
    }

    /// Reference a layer.
    const value_type& operator [] (unsigned int index) const
    {
      typename LayerList::const_iterator layerIt = getLayerConstIterator(index);
      /// @pre !insert => m_layers[index] must exist
      assert(layerIt != m_layers.end());
      return *layerIt;
    }

    /// Reference a layer.
    value_type& operator [] (unsigned int index)
    {
      typename LayerList::iterator layerIt = getLayerIterator(index, false);
      /// @pre !insert => m_layers[index] must exist
      assert(layerIt != m_layers.end());
      return *layerIt;
    }

    /*
     * List accessors
     */

    /// Get beginning iterator.
    iterator begin()
    {
      return m_layers.begin();
    }
    /// Get const beginning iterator.
    const_iterator begin() const
    {
      return m_layers.begin();
    }
    /// Get ending iterator.
    iterator end()
    {
      return m_layers.end();
    }
    /// Get const ending iterator.
    const_iterator end() const
    {
      return m_layers.end();
    }

    /// Get a cached layer iterator.
    /**
     * @post insert => resulting iterator is valid
     */
    const_iterator getLayerConstIterator(unsigned int index) const
    {
      // If we know this index isn't in the list, dispence with the linear searching
      if (index < m_layers.size())
      {
        const_iterator it;
        unsigned int counter = 0;
        // Look for the item in the list
        for (it = m_layers.begin(); it != m_layers.end(); ++it)
        {
          if (counter == index)
          {
            return it;
          }
          ++counter;
        }
        assert(0);
      }

      // If we got here then the index is beyond the end of the list
      return m_layers.end();
    }

    /// Get a cached layer iterator.
    /**
     * @post insert => resulting iterator is valid
     */
    iterator getLayerIterator(unsigned int index, bool insert)
    {
      // If we know this index isn't in the list, dispence with the linear searching
      if (index < m_layers.size())
      {
        iterator it;
        unsigned int counter = 0;
        // Look for the item in the list
        for (it = m_layers.begin(); it != m_layers.end(); ++it)
        {
          if (counter == index)
          {
            // Just insert a new layer at this position if requested
            if (insert)
            {
              it = m_layers.insert(it, 0);
            }
            return it;
          }
          ++counter;
        }
        assert(0);
      }

      // If we got here then the index is beyond the end of the list
      // If we're inserting we can just add a few null layers as necessary
      if (insert)
      {
        m_layers.insert(m_layers.end(), 1 + index - m_layers.size(), 0);
        return --m_layers.end();
      }
      else
      {
        return m_layers.end();
      }
    }

  private:

    /*
     * Variables
     */

    /// Layers.
    LayerList m_layers;

};

#endif // _KwLayerData_h_

