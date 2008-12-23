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

#ifndef _KwCssStyleSheet_h_
#define _KwCssStyleSheet_h_

/**
 * @file KwCssStyleSheet.h
 * @brief Cascading style sheet.
 * @author James Hogan <james@albanarts.com>
 */

#include <QList>

class KwCssStyleRule;

/// Cascading style sheet.
/**
 * Represents a set of style definitions.
 * These definitions may be backed up by a CSS-like file.
 */
class KwCssStyleSheet
{
  public:

    /*
     * Types
     */

    /// List of rules.
    typedef QList<KwCssStyleRule> RuleList;

    /// Constant iterator.
    typedef RuleList::const_iterator ConstIterator;

    /// Iterator.
    typedef RuleList::iterator Iterator;

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwCssStyleSheet();

    /// Copy constructor.
    /**
     * This copies all except the actual styles in each rule which are aliased.
     */
    KwCssStyleSheet(const KwCssStyleSheet& copy);

    /// Destructor.
    virtual ~KwCssStyleSheet();

    /*
     * Main interface
     */

    /// Clear the rules.
    void clear();

    /// Append a rule.
    void addRule(const KwCssStyleRule& rule);

    /// Import another stylesheet.
    void importStyleSheet(const KwCssStyleSheet* styleSheet);

    /*
     * Accessors
     */

    /// Get the rules.
    RuleList& getRules();

    /// Get the constant rules.
    const RuleList& getRules() const;

    /// Convert to CSS-like format.
    QString toString() const;

  private:

    /*
     * Variables
     */

    /// List of style rules.
    RuleList m_rules;
};

#endif // _KwCssStyleSheet_h_

