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

/**
 * @file KwSongdbFilterNode.cpp
 * @brief A node for filtering songs.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbFilterNode.h"
#include "KwSongdbVersionNode.h"
#include "KwSongdb.h"

#include <QSqlQuery>

#include <cassert>

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwSongdbFilterNode::KwSongdbFilterNode(const KwSongdbFilterLevelList* filters, QString label, KwSongdbNode* parent)
: KwSongdbNode(parent)
, m_label(label)
, m_filterLevels(filters)
, m_currentFilter(0)
, m_knownValue()
, m_query(0)
{
  assert(0 != filters);
  assert(filters->size() > 0);
  m_knownValue.next = 0;
  setupQuery();
}

/// Destructor.
KwSongdbFilterNode::~KwSongdbFilterNode()
{
  delete m_query;
}

/*
 * Private constructors
 */

/// Primary constructor.
KwSongdbFilterNode::KwSongdbFilterNode(KwSongdbFilterNode* parent, QString label, QString knownIdExpression, int knownId)
: KwSongdbNode(parent)
, m_label(label)
, m_filterLevels(parent->m_filterLevels)
, m_currentFilter(parent->m_currentFilter + 1)
, m_knownValue()
, m_query(0)
{
  m_knownValue.idExpression = knownIdExpression;
  m_knownValue.idValue = knownId;
  m_knownValue.next = &parent->m_knownValue;
  setupQuery();
}

/*
 * Associated data access
 */

KwSongdbSong* KwSongdbFilterNode::associatedSong()
{
  KnownValue* val = &m_knownValue;
  while (val->next)
  {
    if (val->idExpression == "`Song`.`id`")
    {
      return KwSongdb::self()->songById(val->idValue);
    }
    val = val->next;
  }
  return 0;
}

KwSongdbVersion* KwSongdbFilterNode::associatedSongVersion()
{
  // If only the one child, ask it
  if (getChildCount() == 1)
  {
    KwSongdbNode* child = dynamic_cast<KwSongdbNode*>(getChild(0));
    if (0 != child)
    {
      return child->associatedSongVersion();
    }
  }
  return 0;
}

/*
 * Main interface
 */

/// Get data associated with the node.
QVariant KwSongdbFilterNode::getData(int role, int column)
{
  if (role == Qt::DisplayRole)
  {
    if (column == 0)
    {
      return m_label;
    }
  }
  else if (role == Qt::DecorationRole)
  {
    // Use icon of previous filter
    if (column == 0 && m_currentFilter > 0)
    {
      return (*m_filterLevels)[m_currentFilter - 1].icon;
    }
  }
  return QVariant();
}

/// Get the number of children.
int KwSongdbFilterNode::getChildCount() const
{
  int rows = m_query->size();
  /// @todo implement for db backends that don't support size
  assert(rows != -1);
  return rows;
}

/// Get a child node by index.
KwSongdbNode* KwSongdbFilterNode::_getChild(int index)
{
  bool seekResult = m_query->seek(index);
  if (seekResult)
  {
    /// @todo implement "end condition"
    if (m_currentFilter < m_filterLevels->size() - 1)
    {
      return _newNode(m_query->value(1).toString(),
                      (*m_filterLevels)[m_currentFilter].idExpression, m_query->value(0).toInt());
    }
    else
    {
      assert(m_currentFilter == m_filterLevels->size() - 1);
      return _newFinalNode(m_query->value(1).toString(), m_query->value(0).toInt(),
                           (*m_filterLevels)[m_currentFilter].icon);
    }
  }
  else
  {
    return 0;
  }
}

/// Get flags for this item.
Qt::ItemFlags KwSongdbFilterNode::getFlags(Qt::ItemFlags defaultFlags) const
{
  Qt::ItemFlags flags = defaultFlags;
  // Only allow dragging if only one final song version within
  /// @todo improve so it works at 3 levels
  if (m_currentFilter == m_filterLevels->size()-1 && m_query->size() == 1)
  {
    flags |= Qt::ItemIsDragEnabled;
  }
  return flags;
}

/// Get mime data string for this set of songs.
QString KwSongdbFilterNode::mimeData()
{
  // If a single child node, ask that
  assert(m_currentFilter == m_filterLevels->size()-1 && m_query->size() == 1);
  return _getChild(0)->mimeData();
}

/// Get a new node of this type.
KwSongdbFilterNode* KwSongdbFilterNode::_newNode(QString label, QString idExpression, int idValue)
{
  return new KwSongdbFilterNode(this, label, idExpression, idValue);
}

/// Get a new final node.
KwSongdbNode* KwSongdbFilterNode::_newFinalNode(QString label, int id, const QIcon& icon)
{
  KwSongdbVersionNode* node = new KwSongdbVersionNode(this, label, id);
  node->setIcon(icon);
  return node;
}

/*
 * Private functions
 */

/// Setup the query.
void KwSongdbFilterNode::setupQuery()
{
  if (0 == m_query)
  {
    // Collect joins and where conditions
    QString innerJoins;
    QStringList whereClauses;
    for (int i = 0; i <= m_currentFilter; ++i)
    {
      const KwSongdbFilterLevel& filterI = m_filterLevels->at(i);
      QStringList::const_iterator it;
      for (it = filterI.innerJoinClauses.begin(); it != filterI.innerJoinClauses.end(); ++it)
      {
        innerJoins += "INNER JOIN " + (*it) + " ";
      }
      whereClauses << filterI.whereClauses;
    }
    KnownValue* knownValue = &m_knownValue;
    while (0 != knownValue->next)
    {
      whereClauses << (knownValue->idExpression + " = ?");
      knownValue = knownValue->next;
    }

    // Generate the SQL query
    const KwSongdbFilterLevel& filterLevel = m_filterLevels->at(m_currentFilter);
    QString query = "SELECT " + filterLevel.idExpression    + " AS id,"
                              + filterLevel.labelExpression + " AS label "
                    "FROM " + m_filterLevels->at(0).tableName + " ";
    query += innerJoins;
    if (!whereClauses.empty())
    {
      query += "WHERE " + whereClauses.join(" AND ") + " ";
    }
    if (!filterLevel.orderBy.empty())
    {
      query += "ORDER BY " + filterLevel.orderBy.join(",");
    }
    query += ";";

    // perform the query
    m_query = new QSqlQuery();
    m_query->prepare(query);
    knownValue = &m_knownValue;
    while (0 != knownValue->next)
    {
      m_query->addBindValue(knownValue->idValue);
      knownValue = knownValue->next;
    }
    m_query->exec();
  }
}

