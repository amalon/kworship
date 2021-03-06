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

#ifndef _KwSongdbFilterNode_h_
#define _KwSongdbFilterNode_h_

/**
 * @file KwSongdbFilterNode.h
 * @brief A node for filtering songs.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbNode.h"
#include "KwSongdbFilter.h"

#include <QString>

class QSqlQuery;

/// A node for filtering songs.
class KwSongdbFilterNode : public KwSongdbNode
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwSongdbFilterNode(const KwSongdbFilterLevelList* filters, QString label, KwSongdbNode* parent);

    /// Destructor.
    virtual ~KwSongdbFilterNode();

    /*
     * Associated data access
     */

    virtual KwSongdbSong* associatedSong();
    virtual KwSongdbVersion* associatedSongVersion();

    /*
     * Main interface
     */

    /// Get data associated with the node.
    virtual QVariant getData(int role, int column);

    /// Get the number of children.
    virtual int getChildCount() const;

    /// Get flags for this item.
    virtual Qt::ItemFlags getFlags(Qt::ItemFlags defaultFlags) const;

    /// Get mime data string for this set of songs.
    virtual QString mimeData();

  protected:

    /// Get a child node by index.
    virtual KwSongdbNode* _getChild(int index);

    /// Get a new node of this type.
    KwSongdbFilterNode* _newNode(QString label, QString idExpression, int idValue);

    /// Get a new final node.
    KwSongdbNode* _newFinalNode(QString label, int id, const QIcon& icon);

  private:

    /*
     * Types
     */

    /// A known value from a previous filter.
    struct KnownValue
    {
      QString idExpression;
      int idValue;
      KnownValue* next;
    };

    /*
     * Variables
     */

    /// Label.
    QString m_label;

    /// The shared list of filters.
    const KwSongdbFilterLevelList* m_filterLevels;

    /// The current filter level we're on.
    int m_currentFilter;

    /// The list of known values.
    KnownValue m_knownValue;

    /// Current SQL query.
    QSqlQuery* m_query;

    /*
     * Private constructors
     */

    /// Primary constructor.
    KwSongdbFilterNode(KwSongdbFilterNode* parent, QString label, QString knownIdExpression, int knownId);

    /*
     * Private functions
     */

    /// Setup the query.
    void setupQuery();
};

#endif // _KwSongdbFilterNode_h_

