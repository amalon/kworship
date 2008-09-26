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
 * @file UpSlideNode.cpp
 * @brief A presentations node for a slide.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpSlideNode.h"
#include "UpSlide.h"

#include <KMimeType>
#include <KIcon>

#include <QFileInfo>

#include <cassert>

/*
 * Constructors + destructor.
 */

/// Primary constructor.
UpSlideNode::UpSlideNode(DefaultModelNode* parent, UpSlide* item)
: DefaultModelNode(parent)
, m_item(item)
{
}

/// Destructor.
UpSlideNode::~UpSlideNode()
{
}

/*
 * Accessors
 */

UpSlide* UpSlideNode::getItem()
{
  return m_item;
}

/*
 * Main interface
 */

QVariant UpSlideNode::getData(int role, int column)
{
  if (role == Qt::DisplayRole)
  {
    if (column == 0)
    {
      return QString("slide %d").arg(column);
    }
  }
  return QVariant();
}

