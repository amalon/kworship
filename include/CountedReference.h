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

#ifndef _countedReference_h_
#define _countedReference_h_

/**
 * @file CountedReference.h
 * @brief Counted reference templates.
 * @author James Hogan <james@albanarts.com>
 */

#include <algorithm>

/// Interface to reference counting.
template <typename T>
struct Referencer
{
  /// Unique key type.
  typedef T* Key;

  /// Increment the reference count for @p object.
  static void incRefCount(T* object)
  {
    object->incRefCount();
  }
  
  /// Decrement the reference count for @p object and delete if zero.
  static void decRefCount(T* object)
  {
    if ( 0u == object->decRefCount() )
    {
      delete object;
    }
  }
  
  /// Get the number of references to @p object.
  static unsigned int getRefCount(const T* object)
  {
    return object->getRefCount();
  }

  /// Get the unique key for @p object.
  static const Key& getKey(const T* object)
  {
    return object;
  }
};

/// Base class for reference counting
class ReferenceCounted
{
  public:
    
    /*
      Constructors + destructor
    */
    
    /// Default constructor
    ReferenceCounted()
    : referenceCount(0u)
    {
    }
    
    /// Destructor.
    virtual ~ReferenceCounted()
    {
    }
    
    /*
      Reference counting functions
    */
    
    /// Increment the reference count.
    unsigned int incRefCount()
    {
      return ++referenceCount;
    }
    
    /// Decrement the reference count.
    unsigned int decRefCount()
    {
      return --referenceCount;
    }
    
    /// Get the number of references.
    unsigned int getRefCount() const
    {
      return referenceCount;
    }
    
  private:
    
    /*
      Variables
    */
    
    /// Number of references
    unsigned int referenceCount;
};

/// Extending class for reference counting
template <typename T>
class ReferenceCountedExtension : public T
{
  public:

    /*
     * Types
     */

    /// Default referencing class.
    typedef Referencer<ReferenceCountedExtension> DefaultReferencer;
    
    /*
      Constructors + destructor
    */
    
    /// Default constructor
    ReferenceCountedExtension()
    : T()
    , referenceCount(0u)
    {
    }
    
    /// Destructor.
    virtual ~ReferenceCountedExtension()
    {
    }
    
    /*
      Reference counting functions
    */
    
    /// Increment the reference count.
    unsigned int incRefCount()
    {
      return ++referenceCount;
    }
    
    /// Decrement the reference count.
    unsigned int decRefCount()
    {
      return --referenceCount;
    }
    
    /// Get the number of references.
    unsigned int getRefCount() const
    {
      return referenceCount;
    }
    
  private:
    
    /*
      Variables
    */
    
    /// Number of references
    unsigned int referenceCount;
};

/// Base class for virtual reference counting.
/**
 * Use this as a virtual base class during multiple inheritance.
 * Its quite simply an interface allowing the derived class to implement its
 * own reference counting.
 */
class ReferenceCountedAbstract
{
  public:
    
    /*
      Constructors + destructor
    */
    
    /// Destructor.
    virtual ~ReferenceCountedAbstract()
    {
    }
    
    /*
      Reference counting functions
    */
    
    /// Increment the reference count.
    virtual void incRefCount() = 0;
    
    /// Decrement the reference count.
    virtual void decRefCount() = 0;
    
    /// Get the number of references.
    virtual unsigned int getRefCount() const = 0;
};

/// Base class for virtual reference counting.
/**
 * Use this as a virtual base class during multiple inheritance.
 * It implements a basic reference counter.
 * @param autoDelete Whether to delete when reference reaches zero.
 */
template <bool autoDelete>
class ReferenceCountedVirtual : public virtual ReferenceCountedAbstract
{
  public:

    /*
     * Reference counting functions from ReferenceCountedAbstract
     */

    /// Increment the reference count.
    virtual void incRefCount()
    {
      ++_referenceCount;
    }
    
    /// Decrement the reference count.
    virtual void decRefCount()
    {
      --_referenceCount;
      if ( autoDelete && _referenceCount == 0 )
      {
        delete this;
      }
    }
    
    /// Get the number of references.
    virtual unsigned int getRefCount() const
    {
      return _referenceCount;
    }

  private:

    /*
     * Variables
     */

    /// Reference count
    unsigned int _referenceCount;
};

/// Interface to reference counting.
template <typename T>
struct ReferencerSimple
{
  /// Unique key type.
  typedef T* Key;

  /// Increment the reference count for @p object.
  static void incRefCount(T* object)
  {
    object->incRefCount();
  }
  
  /// Decrement the reference count for @p object.
  static void decRefCount(T* object)
  {
    object->decRefCount();
  }
  
  /// Get the number of references to @p object.
  static unsigned int getRefCount(const T* object)
  {
    return object->getRefCount();
  }

  /// Get the unique key for @p object.
  static const Key& getKey(const T* object)
  {
    return object;
  }
};

// By default use T::DefaultReferencer
template <typename T>
struct DefaultReferencer
{
  typedef typename T::DefaultReferencer Type;
};
// Expands to the default referencer for type T
#define DEFAULT_REFERENCER_TYPE(T) \
  ::DefaultReferencer< T >::Type

// Override default referencer
#define DEFAULT_REFERENCER(T,R) \
  template <> \
  struct DefaultReferencer< T > \
  { \
    typedef R Type; \
  }
// Inherit the default referencer of another class
#define INHERIT_DEFAULT_REFERENCER(T,P) \
  template <> \
  struct DefaultReferencer< T > \
  { \
    typedef DEFAULT_REFERENCER_TYPE(P) Type; \
  }

/// A reference to a counted object.
template <typename T, typename REF = typename DEFAULT_REFERENCER_TYPE(T) >
class Reference
{
  public:

    /*
      Types
    */

    /// Object type.
    typedef T Object;

    /// Referencer structure.
    typedef REF Referencer;
    
    /*
      Constructors + destructor
    */
    
    /// Default/Primary constructor.
    Reference(Object* newObject = 0)
    : object(newObject)
    {
      if ( newObject )
      {
        REF::incRefCount(newObject);
      }
    }
    
    /// Copy constructor.
    Reference(const Reference& ref)
    : object((Object*)ref)
    {
      if ( object )
      {
        Referencer::incRefCount(object);
      }
    }
    
    /// Conversion constructor.
    template <typename U, typename REF2>
    Reference(const Reference<U,REF2>& ref)
    : object(static_cast<T*>(ref))
    {
      if ( object )
      {
        Referencer::incRefCount(object);
      }
    }
    
    /// Destructor.
    ~Reference()
    {
      if ( object )
      {
        Referencer::decRefCount(object);
      }
    }
    
    
    /*
      Object management / efficiency
    */
    
    /// Swap with another object references.
    void swap(Reference& other)
    {
      std::swap(object, other.object);
    }
    
    /// Get the number of references to this object.
    /**
     * @return 0 if nothing is referenced
     */
    unsigned int getRefCount() const
    {
      if ( object )
      {
        return Referencer::getRefCount(object);
      }
      else
      {
        return 0;
      }
    }
    
    
    /*
      Modification operators
    */
    
    /// Assignment to object.
    Reference & operator = (Object* newObject)
    {
      if ( object != newObject )
      {
        if ( object )
        {
          Referencer::decRefCount(object);
        }
        object = newObject;
        if ( newObject )
        {
          Referencer::incRefCount(newObject);
        }
      }
      return *this;
    }
    
    /// Assignment to reference.
    template <typename REF2>
    Reference & operator = (Reference<T,REF2>& newObject)
    {
      if ( object != (Object*)newObject )
      {
        if ( object )
        {
          Referencer::decRefCount(object);
        }
        object = (Object*)newObject;
        if ( object )
        {
          Referencer::incRefCount(object);
        }
      }
      return *this;
    }
    
    /*
      Access operators
    */
    
    /// Cast to Object*.
    operator Object* () const
    {
      return object;
    }

    /// Dereference.
    Object* operator -> () const
    {
      return object;
    }

    /*
     * Casting
     */

    /// Dynamic cast.
    template <typename U>
    friend U dynamicCast(const Reference& ref)
    {
      return dynamic_cast<U>(ref.object);
    }
    
  protected:
    
    /*
      Variables
    */
    
    /// Pointer to the object.
    Object* object;
};

namespace std
{
  /*
    std::swap specialisations
  */
  template <typename T, typename REF>
  void swap(Reference<T,REF>& a, Reference<T,REF>& b)
  {
    a.swap(b);
  }
};

#endif // _countedReference_h_
