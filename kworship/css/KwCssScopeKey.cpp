/**
 * @file KwCssScopeKey.cpp
 * @brief Scope type and name pair.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssScopeKey.h"

#include <cassert>

/*
 * Static variables
 */

/// Last valid id.
KwCssScopeKey::ScopeTypeId KwCssScopeKey::s_lastValidTypeId = -1;

/// Scope type names to scope type ids.
KwCssScopeKey::ScopeTypeNameIdMapping KwCssScopeKey::s_scopeTypeNameToId;

/// Scope type id to scope type name.
KwCssScopeKey::ScopeTypeIdNameMapping KwCssScopeKey::s_scopeTypeIdToName;

/*
 * Static scope type registration
 */

/// Register a type of scope.
KwCssScopeKey::ScopeTypeId KwCssScopeKey::registerScopeType(ScopeTypeName typeName)
{
  ScopeTypeNameIdMapping::const_iterator it = s_scopeTypeNameToId.find(typeName);
  if (it != s_scopeTypeNameToId.end())
  {
    return *it;
  }
  else
  {
    ++s_lastValidTypeId;
    s_scopeTypeNameToId[typeName] = s_lastValidTypeId;
    s_scopeTypeIdToName.push_back(typeName);
    return s_lastValidTypeId;
  }
}

/// Get the id for a scope type name.
KwCssScopeKey::ScopeTypeId KwCssScopeKey::getScopeTypeId(ScopeTypeName typeName)
{
  ScopeTypeNameIdMapping::const_iterator it = s_scopeTypeNameToId.find(typeName);
  if (it != s_scopeTypeNameToId.end())
  {
    return *it;
  }
  else
  {
    return -1;
  }
}

/// Get the name for a scope type id.
KwCssScopeKey::ScopeTypeName KwCssScopeKey::getScopeTypeName(ScopeTypeId typeId)
{
  if (typeId >= 0 && typeId <= s_scopeTypeIdToName.size())
  {
    return s_scopeTypeIdToName[typeId];
  }
  else
  {
    return "";
  }
}

/// Find whether a scope type id is valid.
bool KwCssScopeKey::isScopeTypeValid(ScopeTypeId typeId)
{
  return typeId >= 0;
}

/*
 * Constructors + destructors
 */

/// Primary constructor.
KwCssScopeKey::KwCssScopeKey(ScopeTypeName typeName, ScopeName name)
: m_typeId(getScopeTypeId(typeName))
, m_name(name)
{
  /// @pre typeName must be registered if specified.
  assert((typeName.size() > 0 || isScopeTypeValid(m_typeId)) &&"Invalid scope type");
  /// @pre either typeName or name must be specified.
  assert((isScopeTypeValid(m_typeId) || name.size() > 0) &&"Non specific key");
}

/// Primary constructor.
KwCssScopeKey::KwCssScopeKey(ScopeTypeId typeId, ScopeName name)
: m_typeId(typeId)
, m_name(name)
{
  /// @pre either typeName or name must be specified.
  assert((isScopeTypeValid(typeId) || name.size() > 0) &&"Non specific key");
}

/// Non virtual destructor.
KwCssScopeKey::~KwCssScopeKey()
{
}

/*
 * Accessors
 */

/// Find whether the type part of the key is specified.
bool KwCssScopeKey::isTypeSpecified() const
{
  return isScopeTypeValid(m_typeId);
}

/// Get the scope type id.
KwCssScopeKey::ScopeTypeId KwCssScopeKey::getTypeId() const
{
  return m_typeId;
}

/// Get the scope type name.
KwCssScopeKey::ScopeTypeName KwCssScopeKey::getTypeName() const
{
  return getScopeTypeName(m_typeId);
}

/// Find whether the name part of the key is specified.
bool KwCssScopeKey::isNameSpecified() const
{
  return m_name.size() > 0;
}

/// Get the scope name.
KwCssScopeKey::ScopeName KwCssScopeKey::getName() const
{
  return m_name;
}

