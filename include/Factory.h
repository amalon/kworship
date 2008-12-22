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

    /** Remove a type from the factory.
     * @param key Identifier used to construct.
     */
    bool removeType(const KEY& key)
    {
      
      typename ConstructorHash::iterator it = m_constructors.find(key);
      if (it != m_constructors.end())
      {
        delete *it;
        m_constructors.erase(it);
        return true;
      }
      return false;
    }

    /*
     * Construction
     */

    BASE* construct(const KEY& key)
    {
      return constructFromPack(key, TUPLE::pack());
    }
    template <typename Param1>
    BASE* construct(const KEY& key, const Param1& param1)
    {
      return constructFromPack(key, TUPLE::pack(param1));
    }
    template <typename Param1, typename Param2>
    BASE* construct(const KEY& key, const Param1& param1, const Param2& param2)
    {
      return constructFromPack(key, TUPLE::pack(param1, param2));
    }

    /** Construct a type using a pack of arguments.
     * @param key identifier of type to construct.
     * @param pack pack of arguments.
     */
    BASE* constructFromPack(const KEY& key, const typename TUPLE::Pack& pack)
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

    BASE* singleton(const KEY& key)
    {
      return singletonFromPack(key, TUPLE::pack());
    }
    template <typename Param1>
    BASE* singleton(const KEY& key, const Param1& param1)
    {
      return singletonFromPack(key, TUPLE::pack(param1));
    }
    template <typename Param1, typename Param2>
    BASE* singleton(const KEY& key, const Param1& param1, const Param2& param2)
    {
      return singletonFromPack(key, TUPLE::pack(param1, param2));
    }

    /** Get a singleton of a type using a pack of arguments.
     * @param key identifier of type to construct.
     * @param pack pack of arguments.
     */
    BASE* singletonFromPack(const KEY& key, const typename TUPLE::Pack& pack)
    {
      typename ConstructorHash::const_iterator it = m_constructors.constFind(key);
      if (it != m_constructors.constEnd())
      {
        return (*it)->singleton(pack);
      }
      else
      {
        return 0;
      }
    }

    /// Delete any existing singleton of a type.
    void deleteSingleton(const KEY& key)
    {
      typename ConstructorHash::const_iterator it = m_constructors.constFind(key);
      if (it != m_constructors.constEnd())
      {
        (*it)->deleteSingleton();
      }
    }

    /// Delete all singletons.
    void deleteAllSingletons()
    {
      foreach (BaseConstructor* constructor, m_constructors)
      {
        constructor->deleteSingleton();
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
        BaseConstructor()
        : m_singleton(0)
        {
        }
        virtual ~BaseConstructor()
        {
          delete m_singleton;
        }
        /// Construct an instance of a dervied type.
        virtual BASE* construct(const typename TUPLE::Pack& pack) const = 0;
        /// Get a singleton object, constructing if necessary.
        BASE* singleton(const typename TUPLE::Pack& pack)
        {
          if (0 == m_singleton)
          {
            m_singleton = construct(pack);
          }
          return m_singleton;
        }
        /// Delete singleton if it exists.
        void deleteSingleton()
        {
          delete m_singleton;
          m_singleton = 0;
        }

      private:
        // No copy construction
        BaseConstructor(const BaseConstructor&);

        BASE* m_singleton;
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

