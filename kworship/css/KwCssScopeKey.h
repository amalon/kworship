#ifndef _KwCssScopeKey_h_
#define _KwCssScopeKey_h_

/**
 * @file KwCssScopeKey.h
 * @brief Scope type and name pair.
 * @author James Hogan <james@albanarts.com>
 */

#include <QString>
#include <QHash>
#include <QVector>

/// Scope type and name pair.
class KwCssScopeKey
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

