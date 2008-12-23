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

#ifndef _KwCssStyleRule_h_
#define _KwCssStyleRule_h_

/**
 * @file KwCssStyleRule.h
 * @brief Rule for apply cascading styles.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssScopeKey.h"
#include "KwCssStyles.h"

#include "CountedReference.h"

#include <QString>
#include <QStringList>
#include <QSet>
#include <QList>

/// Rule for apply cascading styles.
class KwCssStyleRule
{
  public:

    /*
     * Types
     */

    /// List of keys.
    typedef QList<KwCssScopeKey> KeyList;

    /// Set of strings.
    typedef QSet<QString> StringSet;

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwCssStyleRule();

    /// Destructor.
    virtual ~KwCssStyleRule();

    /*
     * Main interface.
     */

    /// Set the set of critieria keys.
    void setCriteriaKeys(const KeyList& keys);

    /// Set the set of required classes.
    void setCriteriaClasses(const StringSet& classes);

    /// Set a style.
    void setRawStyle(QString name, KwCssAbstractStyle* style);

    /// Set a style of a particular type.
    template <typename T>
    void setStyle(QString name, const T& value)
    {
      m_styles->setStyle<T>(name, value);
    }

    /*
     * Accessors
     */

    /// Get the list of criteria keys.
    KeyList& getCriteriaKeys();

    /// Get the set of criteria classes.
    StringSet& getCriteriaClasses();

    /// Get the list of included styles.
    const StringSet& getIncludedStyles() const;

    /// Get the styles.
    const ReferenceCountedExtension<KwCssStyles>* getStyles() const;

    /// Convert to CSS-like format.
    QString toString() const;

  private:

    /*
     * Matching criteria
     */

    /// List of (sequences of scope keys to match in order).
    KeyList m_criteriaKeys;

    /// Classes required to match.
    StringSet m_criteriaClasses;

    /*
     * Variables
     */

    /// Names of included classes.
    StringSet m_includedStyles;

    /// The styles.
    Reference<ReferenceCountedExtension<KwCssStyles> > m_styles;
};

#endif // _KwCssStyleRule_h_

