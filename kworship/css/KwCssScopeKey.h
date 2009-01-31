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

#ifndef _KwCssScopeKey_h_
#define _KwCssScopeKey_h_

/**
 * @file KwCssScopeKey.h
 * @brief Scope type and name pair.
 * @author James Hogan <james@albanarts.com>
 */

#include <kdemacros.h>

#include <QString>
#include <QHash>
#include <QVector>

/// Scope type and name pair.
class KDE_EXPORT KwCssScopeKey
{
  public:

    /*
     * Types
     */

    /// Scope type name type.
    typedef QString ScopeTypeName;

    /// Scope type identifier type.
    typedef int ScopeTypeId;

    /// Scope name type.
    typedef QString ScopeName;

    /*
     * Static scope type registration
     */

    /// Register a type of scope.
    static ScopeTypeId registerScopeType(ScopeTypeName typeName);

    /// Get the id for a scope type name.
    static ScopeTypeId getScopeTypeId(ScopeTypeName typeName);

    /// Get the name for a scope type id.
    static ScopeTypeName getScopeTypeName(ScopeTypeId typeId);

    /// Find whether a scope type id is valid.
    static bool isScopeTypeValid(ScopeTypeId typeId);

  private:

    /*
     * Private types
     */

    /// Mapping from scope type names to ids.
    typedef QHash<ScopeTypeName,ScopeTypeId> ScopeTypeNameIdMapping;

    /// Mapping from scope type ids to names.
    typedef QVector<ScopeTypeName> ScopeTypeIdNameMapping;

    /*
     * Static variables
     */

    /// Last valid id.
    static ScopeTypeId s_lastValidTypeId;

    /// Scope type names to scope type ids.
    static ScopeTypeNameIdMapping s_scopeTypeNameToId;

    /// Scope type id to scope type name.
    static ScopeTypeIdNameMapping s_scopeTypeIdToName;

  public:

    /*
     * Constructors + destructors
     */

    /// Primary constructor.
    KwCssScopeKey(ScopeTypeName typeId, ScopeName name = "");

    /// Primary constructor.
    KwCssScopeKey(ScopeTypeId typeId, ScopeName name = "");

    /// Non virtual destructor.
    ~KwCssScopeKey();

    /*
     * Accessors
     */

    /// Find whether the type part of the key is specified.
    bool isTypeSpecified() const;

    /// Get the scope type id.
    ScopeTypeId getTypeId() const;

    /// Get the scope type name.
    ScopeTypeName getTypeName() const;

    /// Find whether the name part of the key is specified.
    bool isNameSpecified() const;

    /// Get the scope name.
    ScopeName getName() const;

  private:

    /*
     * Variables
     */

    /// Scope type id.
    ScopeTypeId m_typeId;

    /// Scope name.
    ScopeName m_name;
    
};

#endif // _KwCssScopeKey_h_

