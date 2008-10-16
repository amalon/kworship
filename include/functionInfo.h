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

#ifndef _functionInfo_h_
#define _functionInfo_h_

#include "repeatMacros.h"

namespace meta
{
  template <typename F>
  struct Tuple;
#define META_TUPLE(ARGS) ::meta::Tuple<void (*)ARGS>
  
  template <typename F, int P>
  struct ParameterInfo;

  // Number of arguments of a function
  template <typename F>
  struct FunctionInfo;


  // Macros to make this easier

  // Parameter list, e.g. "typename Param0; typename Param1;"
#define FUNCTION_INFO_PARAM_INSTANTIATION(A,B,N)  Param##N param##N;
#define FUNCTION_INFO_PARAM_INSTANTIATIONS(N) REPEATB(FUNCTION_INFO_PARAM_INSTANTIATION,0,0,N)
  // Parameter list, e.g. "typename Param0, typename Param1"
#define FUNCTION_INFO_TEMPLATE_PARAMETER(A,B,N)  typename Param##N
#define FUNCTION_INFO_TEMPLATE_PARAMETERS(N) REPEATB_LIST(FUNCTION_INFO_TEMPLATE_PARAMETER,0,0,N)
  // Parameter list, e.g. ", typename Param0, typename Param1"
#define FUNCTION_INFO_TEMPLATE_PARAMETER_TAIL(A,B,N)  , typename Param##N
#define FUNCTION_INFO_TEMPLATE_PARAMETERS_TAIL(N) REPEATB(FUNCTION_INFO_TEMPLATE_PARAMETER_TAIL,0,0,N)
  // Argument list, e.g. "(Param0 param0, Param1 param1)"
#define FUNCTION_INFO_PARAMETER(A,B,N)   Param##N param##N
#define FUNCTION_INFO_PARAMETERS(N) \
  ( REPEATB_LIST(FUNCTION_INFO_PARAMETER,0,0,N) )
  // Tail argument list, e.g. ", Param0, Param1"
#define FUNCTION_INFO_PARAMETER_TAIL(A,B,N) , Param##N
#define FUNCTION_INFO_PARAMETERS_TAIL(N) \
  REPEATB(FUNCTION_INFO_PARAMETER_TAIL,0,0,N)
  // Argument list, e.g. "(param0, param1)"
#define FUNCTION_INFO_ARGUMENT(A,B,N)   param##N
#define FUNCTION_INFO_ARGUMENTS(N) \
  ( REPEATB_LIST(FUNCTION_INFO_ARGUMENT,0,0,N) )
  // Unpack Argument list, e.g. "(P.param0, P.param1)"
#define FUNCTION_INFO_UNPACK_ARGUMENT(P,B,N)   (P).param##N
#define FUNCTION_INFO_UNPACK_ARGUMENTS(P,N) \
  ( REPEATB_LIST(FUNCTION_INFO_UNPACK_ARGUMENT,P,0,N) )

  // Parameter template instantiation
#define PARAMETER_INFO(T,N) \
  template <FUNCTION_INFO_TEMPLATE_PARAMETERS(T) > \
  struct ParameterInfo<void (*)FUNCTION_INFO_PARAMETERS(T),N> \
  { \
    typedef Param##N Type; \
  };

  // Function length template instantiation
#define FUNCTION_INFO(N) \
  template <FUNCTION_INFO_TEMPLATE_PARAMETERS(N) > \
  struct Tuple<void (*)FUNCTION_INFO_PARAMETERS(N)> \
  { \
    enum \
    { \
      length = N \
    }; \
    struct Pack \
    { \
      /* A member for each item */ \
      FUNCTION_INFO_PARAM_INSTANTIATIONS(N) \
      /* Construct a new CTYPE using the pack as arguments */ \
      template <typename CTYPE> \
      CTYPE* construct() const \
      { \
        return new CTYPE FUNCTION_INFO_ARGUMENTS(N); \
      } \
    }; \
    static struct Pack pack FUNCTION_INFO_PARAMETERS(N) \
    { \
      Pack myPack = { REPEATB_LIST(FUNCTION_INFO_ARGUMENT,0,0,N) }; \
      return myPack; \
    } \
    template <int id> \
    struct Param : public ParameterInfo<void (*)FUNCTION_INFO_PARAMETERS(N), id> \
    { \
    }; \
    template <typename Ret> \
    struct Return \
    { \
      typedef Ret (Signiture)FUNCTION_INFO_PARAMETERS(N); \
      typedef Ret (*Pointer)FUNCTION_INFO_PARAMETERS(N); \
      typedef FunctionInfo<Pointer> Info; \
    }; \
    template <typename NewArg> \
    struct Unshift \
    { \
      typedef void (*Pointer)(NewArg FUNCTION_INFO_PARAMETERS_TAIL(N)); \
      typedef Tuple<Pointer> Info; \
    }; \
  }; \
  template <typename Ret FUNCTION_INFO_TEMPLATE_PARAMETERS_TAIL(N) > \
  struct FunctionInfo<Ret (*)FUNCTION_INFO_PARAMETERS(N)> \
  { \
    typedef Ret Return; \
    typedef Ret (*Pointer)FUNCTION_INFO_PARAMETERS(N); \
    typedef Tuple<void (*)FUNCTION_INFO_PARAMETERS(N)> Params; \
    template <typename FUNCTOR> \
    static Ret unpack(typename Params::Pack package) \
    { \
      return FUNCTOR::call FUNCTION_INFO_UNPACK_ARGUMENTS(package,N); \
    } \
    template <typename NewArg> \
    struct Unshift \
    { \
      typedef Ret (*Pointer)(NewArg FUNCTION_INFO_PARAMETERS_TAIL(N)); \
      typedef FunctionInfo<Pointer> Info; \
    }; \
  }; \
  REPEATA(PARAMETER_INFO, N, N)


  REPEAT(FUNCTION_INFO, 8)

#undef FUNCTION_INFO_PARAMETER
#undef FUNCTION_INFO_PARAMETERS
#undef FUNCTION_INFO_ARGUMENT
#undef FUNCTION_INFO_POINTER_TYPE
#undef PARAMETER_INFO
#undef FUNCTION_INFO
}

#endif // _functionInfo_h_

