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

#ifndef _VTable_h_
#define _VTable_h_

/**
 * @file VTable.h
 * @brief Generic run-time VTable implementation, useful for filter plugins.
 * @author James Hogan <james@albanarts.com>
 */

#include "functionInfo.h"

/// Generic run-time VTable implementation.
/**
 * @param Base Base class.
 * @param Sig Signiture of virtual function.
 */
template <typename Base, typename Sig>
class VTable
{
    /*
     * Type declarations
     */

    class BaseImplementation;
    template <typename T> class Implementation;

  public:

    /*
     * Constructors + destructor
     */

    /// Default constructor.
    VTable()
    {
    }

    /// Destructor.
    virtual ~VTable()
    {
      foreach (BaseImplementation* impl, m_implementations)
      {
        delete impl;
      }
    }

    /*
     * Main interface
     */

    /// Add an implementation.
    /**
     * @param T Derived class.
     * @param impl Function pointer to implementation.
     */
    template <typename F>
    void addImplementation(F impl)
    {
      m_implementations += new PointerImplementation<typename meta::PointerInfo<typename meta::ParameterInfo<F,0>::Type>::Type>(impl);
    }
    /*
    template <typename T>
    void addImplementation(typename meta::FunctionInfo<Sig>::template Unshift<T*>::Pointer impl)
    {
      m_implementations += new PointerImplementation<T>(impl);
    }
    */
    template <typename T, typename FUNCTOR>
    void addImplementation()
    {
      m_implementations += new FunctorImplementation<T, FUNCTOR>();
    }

    bool operator () (Base* base) const { return callPack(base, meta::FunctionInfo<Sig>::Params::pack()); }
    template <typename P1>
    bool operator () (Base* base, P1 p1) const { return callPack(base, meta::FunctionInfo<Sig>::Params::pack(p1)); }
    template <typename P1, typename P2>
    bool operator () (Base* base, P1 p1, P2 p2) const { return callPack(base, meta::FunctionInfo<Sig>::Params::pack(p1,p2)); }
    template <typename P1, typename P2, typename P3>
    bool operator () (Base* base, P1 p1, P2 p2, P3 p3) const { return callPack(base, meta::FunctionInfo<Sig>::Params::pack(p1,p2,p3)); }

    bool callPack(Base* base, const typename meta::FunctionInfo<Sig>::Params::Pack& params) const
    {
      foreach (BaseImplementation* impl, m_implementations)
      {
        if (impl->call(base, params))
        {
          return true;
        }
      }
      return false;
    }

    bool test(Base* base)
    {
      foreach (BaseImplementation* impl, m_implementations)
      {
        if (impl->test(base))
        {
          return true;
        }
      }
      return false;
    }

  private:

    /*
     * Types
     */

    class BaseImplementation
    {
      public:
        virtual ~BaseImplementation()
        {
        }
        virtual bool call(Base* base, const typename meta::FunctionInfo<Sig>::Params::Pack& params) const = 0;
        virtual bool test(Base* base) const = 0;
    };

    template <typename T, typename FUNCTOR>
    class FunctorImplementation : public BaseImplementation
    {
      public:
        virtual ~FunctorImplementation()
        {
        }
        virtual bool call(Base* base, const typename meta::FunctionInfo<Sig>::Params::Pack& params) const
        {
          T* derived = dynamic_cast<T*>(base);
          if (derived != 0)
          {
            meta::FunctionInfo<Sig>::template unpack<FUNCTOR, T*>(derived, params);
            return true;
          }
          else
          {
            return false;
          }
        }
        virtual bool test(Base* base) const
        {
          return dynamic_cast<T*>(base) != 0;
        }
      private:
        typename meta::FunctionInfo<Sig>::template Unshift<T>::Pointer m_impl;
    };

    template <typename T>
    class PointerImplementation : public BaseImplementation
    {
      public:
        PointerImplementation(typename meta::FunctionInfo<Sig>::template Unshift<T*>::Pointer impl)
        : m_impl(impl)
        {
        }
        virtual ~PointerImplementation()
        {
        }
        virtual bool call(Base* base, const typename meta::FunctionInfo<Sig>::Params::Pack& params) const
        {
          T* derived = dynamic_cast<T*>(base);
          if (derived != 0)
          {
            meta::FunctionInfo<Sig>::template call(m_impl, derived, params);
            return true;
          }
          else
          {
            return false;
          }
        }
        virtual bool test(Base* base) const
        {
          return dynamic_cast<T*>(base) != 0;
        }
      private:
        typename meta::FunctionInfo<Sig>::template Unshift<T*>::Pointer m_impl;
    };

    /*
     * Variables
     */

    /// Have a big list of implementations.
    QList<BaseImplementation*> m_implementations;

};

#endif // _VTable_h_
