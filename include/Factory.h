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

#ifndef _Factory_h_
#define _Factory_h_

/**
 * @file Factory.h
 * @brief A generic object factory.
 * @author James Hogan <james@albanarts.com>
 */

#include "functionInfo.h"

#include <QHash>

/** A generic object factory.
 * Types can be registered to this class and then constructed using a key.
 */
template <typename KEY, typename BASE, typename TUPLE>
class Factory
{
  public:
    
    /*
     * Constructors + destructor
     */

    /// Default constructor.
    Factory()
    : m_constructors()
    {
    }

    /// Destructor.
    ~Factory()
    {
      foreach (BaseConstructor* constructor, m_constructors)
      {
        delete constructor;
      }
    }

    /*
     * Type registration
     */

    /** Add a type to the factory.
     * @param T Type to add.
     * @param key Identifier used to construct.
     */
    template <typename T>
    bool addType(const KEY& key)
    {
      typename ConstructorHash::const_iterator it = m_constructors.constFind(key);
      if (it == m_constructors.constEnd())
      {
        m_constructors[key] = new Constructor<T>();
        return true;
      }
      return false;
    }

    /*
     * Construction
     */

    BASE* construct(KEY key)
    {
      return constructFromPack(key, TUPLE::pack());
    }
    template <typename Param1>
    BASE* construct(KEY key, const Param1& param1)
    {
      return constructFromPack(key, TUPLE::pack(param1));
    }
    template <typename Param1, typename Param2>
    BASE* construct(KEY key, const Param1& param1, const Param2& param2)
    {
      return constructFromPack(key, TUPLE::pack(param1, param2));
    }

    /** Construct a type using a pack of arguments.
     * @param key identifier of type to construct.
     * @param pack pack of arguments.
     */
    BASE* constructFromPack(KEY key, const typename TUPLE::Pack& pack)
    {
      typename ConstructorHash::const_iterator it = m_constructors.constFind(key);
      if (it != m_constructors.constEnd())
      {
        return (*it)->construct(pack);
      }
      else
      {
        return 0;
      }
    }

  private:

    /*
     * Types
     */

    /// Base constructor class.
    class BaseConstructor
    {
      public:
        virtual ~BaseConstructor() {}
        /// Construct an instance of a dervied type.
        virtual BASE* construct(const typename TUPLE::Pack& pack) const = 0;
    };

    /** Type specific generic constructor.
     * @param TYPE Type to construct.
     */
    template <typename TYPE>
    class Constructor : public BaseConstructor
    {
      public:
        virtual ~Constructor() {}
        virtual BASE* construct(const typename TUPLE::Pack& pack) const
        {
          return pack.template construct<TYPE>();
        }
    };

    /// Hash of keys to constructors.
    typedef QHash<KEY, BaseConstructor*> ConstructorHash;

    /*
     * Variables
     */

    /// Constructors by key.
    ConstructorHash m_constructors;
};

#endif // _Factory_h_

