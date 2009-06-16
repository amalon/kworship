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

#ifndef _KwCssStandardise_h_
#define _KwCssStandardise_h_

/**
 * @file KwCssStandardise.h
 * @brief Macros for css standardisation.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssScope.h"
#include "KwCssSchema.h"

#include <KwExport.h>

/// Simple class for accessing a style.
template <typename T>
class KWMAIN_EXPORT KwCssStyleAccessor
{
  public:
    virtual ~KwCssStyleAccessor()
    {
    }
    /*
     * Main interface
     */
    T operator () (const KwCssScope* scope) const
    {
      return scope->getStyles().template getStyle<T>(m_name);
    }

    void registerToSchema(KwCssSchema* schema) const
    {
      schema->registerProperty<T>(m_name);
    }
  protected:
    QString m_name;
};

#define KWCSS_SCHEMA \
  inline KwCssSchema* schema() \
  { \
    static KwCssSchema* s = 0; \
    if (0 == s) \
    { \
      s = new KwCssSchema; \
    } \
    return s; \
  }

/// Start the root css namespace.
#define KWCSS_ROOT_NAMESPACE(NAME) \
  namespace NAME \
  { \
    inline QString _scopeName() \
    { \
      return #NAME; \
    }

/// Start a non-root css namespace.
#define KWCSS_START_NAMESPACE(PREV,NAME) \
  namespace NAME \
  { \
    inline QString _scopeName() \
    { \
      return #PREV "." #NAME; \
    }

/// End a css namespace.
#define KWCSS_END_NAMESPACE() \
  };

/// Define a property in a css namespace.
#define KWCSS_DEFINE_PROPERTY(TYPE, LNAME) \
  class KWMAIN_EXPORT Acc_##LNAME : public KwCssStyleAccessor< TYPE > \
  { \
    public: \
      Acc_##LNAME() \
      { \
        m_name = _scopeName(); \
        m_name.append("." #LNAME); \
        registerToSchema(schema()); \
      } \
  }; \
  KWMAIN_EXPORT KWCSS_EXTERN Acc_##LNAME LNAME;

#define KWCSS_EXTERN extern

#endif // _KwCssStandardise_h_

