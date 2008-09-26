/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   KWorship is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   KWorship is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with KWorship.  If not, see <http://www.gnu.org/licenses/>.     *
 ***************************************************************************/

/**
 * @file UpBackendNode.cpp
 * @brief A presentations node for a backend.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpBackendNode.h"
#include "UpBackend.h"

#include <KIcon>

#include <cassert>

/*
 * Constructors + destructor.
 */

/// Primary constructor.
UpBackendNode::UpBackendNode(DefaultModelNode* parent, UpBackend* item)
: DefaultModelNode(parent)
, m_item(item)
{
}

/// Destructor.
UpBackendNode::~UpBackendNode()
{
}

/*
 * Accessors
 */

UpBackend* UpBackendNode::getItem()
{
  return m_item;
}

/*
 * Main interface
 */

QVariant UpBackendNode::getData(int role, int column)
{
  if (role == Qt::DisplayRole)
  {
    if (column == 0)
    {
      return m_item->name();
    }
  }
  else if (role == Qt::DecorationRole)
  {
    if (column == 0)
    {
      return KIcon("playlist");
    }
  }
  return QVariant();
}

int UpBackendNode::getChildCount() const
{
  return 0;
}

DefaultModelNode* UpBackendNode::_getChild(int index)
{
  Q_UNUSED(index)
  return 0;
}

