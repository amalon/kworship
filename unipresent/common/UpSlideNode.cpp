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
      return m_item->title();
    }
  }
  else if (role == Qt::DecorationRole)
  {
    if (column == 0)
    {
      QPixmap pixmap = m_item->preview();
      if (!pixmap.isNull())
      {
        return pixmap;
      }
    }
  }
  return QVariant();
}

