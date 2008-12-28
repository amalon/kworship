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

#ifndef _KwCssSchema_h_
#define _KwCssSchema_h_

/**
 * @file KwCssSchema.h
 * @brief Schema of styles.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssScope.h"

#include <QString>
#include <QHash>

#include <iostream>
/// Schema of styles.
class KwCssSchema
{
  public:

    /*
     * Constructors + destructor
     */

    /// Default constructor
    KwCssSchema()
    {
    }

    /*
     * Main interface
     */

    /// Register a new property.
    template <typename T>
    void registerProperty(const QString& name)
    {
      m_constructors[name] = &KwCssConstruct<T>;
    }

    /// Construct from an unprocessed string and a style name.
    KwCssAbstractStyle* construct(const QString& name, const KwCssUnprocessed& value) const
    {
      KwCssAbstractStyle* result = 0;
      if (m_constructors.contains(name))
      {
        result = m_constructors[name](value);
      }
      if (0 == result)
      {
        result = new KwCssStyle<KwCssUnprocessed>(value);
      }
      return result;
    }

  private:
    
    /*
     * Variables
     */

    /// Constructor function.
    typedef KwCssAbstractStyle* Constructor(const KwCssUnprocessed& value);
    /// Hash of style names to constructors.
    QHash<QString, Constructor*> m_constructors;
};

#endif // _KwCssSchema_h_

