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

#ifndef _KwCssScope_h_
#define _KwCssScope_h_

/**
 * @file KwCssScope.h
 * @brief Cascading style scope.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssScopeKey.h"
#include "KwCssStyleSheet.h"
#include "KwCssStyles.h"
#include "KwCssStyleStates.h"

#include <KwExport.h>

#include <QStringList>
#include <QString>
#include <QSet>
#include <QList>

class KwCssStyleSheet;
class KwResourceManager;
class QDomDocument;
class QDomElement;

#define KW_CSS_SCOPE(TYPE_NAME) \
  public: \
    /** Get the type id corresponding to this type statically. */ \
    static KwCssScopeKey::ScopeTypeId scopeTypeId() \
    { \
      static KwCssScopeKey::ScopeTypeId id = KwCssScopeKey::registerScopeType(TYPE_NAME); \
      return id; \
    } \
    /** Get the type id corresponding to this type virtually. */ \
    virtual KwCssScopeKey::ScopeTypeId getTypeId() const \
    { \
      return scopeTypeId(); \
    }

/// Cascading style scope.
class KWMAIN_EXPORT KwCssScope
{
    KW_CSS_SCOPE("scope")

  public:

    /*
     * Constructors + destructors
     */

    /// Primary constructor.
    KwCssScope(KwCssSchema* schema, KwCssScope* parent = 0);

    /// Destructor.
    virtual ~KwCssScope();

    /*
     * DOM filters
     */

    /// Import the style information from a DOM.
    void importStylesFromDom(const QDomElement& element, KwResourceManager* resourceManager);

    /// Export the style information to a DOM.
    void exportStylesToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const;

    /*
     * Main interface
     */

    /// Add a stylesheet for this scope.
    void addStyleSheet(KwCssStyleSheet* styleSheet);

    /// Set an explicit style.
    template <typename T>
    void setExplicitStyle(QString name, const T& value)
    {
      m_styles.setStyle<T>(name, value);
      recalculateStyles();
    }

    /// Add a class to this scope.
    void addClass(QString className);

    /// Get all the styles included in this scope.
    const KwCssStyleStates& getStyles() const;

    /// Recalculate all styles.
    void recalculateStyles();

    /*
     * Accessors
     */

    /// Find whether the scope is effectively empty.
    bool isScopeEmpty() const;

    /// Get explicit styles.
    const KwCssStyles& getExplicitStyles() const;

    /// Get the scope's key.
    KwCssScopeKey getKey() const;

    /// Find whether a scope key matches this scope.
    bool isKeyMatching(KwCssScopeKey key) const;

    /*
     * Mutators
     */

    /// Set the parent scope.
    void setParentScope(KwCssScope* parent);

  private:

    /*
     * Types
     */

    /// Set of scopes.
    typedef QSet<KwCssScope*> ScopeSet;

    /// Set of strings.
    typedef QSet<QString> StringSet;

    /// List of style sheets.
    typedef QList<KwCssStyleSheet*> StyleSheetList;

    /*
     * Basic data
     */

    /// Style schema.
    KwCssSchema* m_schema;

    /// Parent scope.
    KwCssScope* m_parentScope;

    /// Set of child scopes.
    ScopeSet m_childScopes;

    /// Name of the scope.
    KwCssScopeKey::ScopeName m_name;

    /*
     * Variables
     */

    /// Classes enabled by default in this scope.
    StringSet m_classes;

    /// Style sheets.
    StyleSheetList m_styleSheets;

    /// Explicit style overrides.
    KwCssStyles m_styles;

    /*
     * Cache
     */

    /// Cached styles.
    KwCssStyleStates m_cachedStyles;

    /// Cached stylesheet accumulation.
    KwCssStyleSheet m_cachedStyleSheet;

    /// Cached total class list.
    StringSet m_cachedClasses;
};

#endif // _KwCssScope_h_

