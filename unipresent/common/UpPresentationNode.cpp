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
 * @file UpPresentationNode.cpp
 * @brief A presentations node for a backend.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpPresentationNode.h"
#include "UpPresentation.h"
#include "UpSlideNode.h"

#include <KMimeType>
#include <KIcon>

#include <QFileInfo>

#include <cassert>

/*
 * Constructors + destructor.
 */

/// Primary constructor.
UpPresentationNode::UpPresentationNode(DefaultModelNode* parent, UpPresentation* item)
: DefaultModelNode(parent)
, m_item(item)
{
}

/// Destructor.
UpPresentationNode::~UpPresentationNode()
{
}

/*
 * Accessors
 */

UpPresentation* UpPresentationNode::getItem()
{
  return m_item;
}

/*
 * Main interface
 */

QVariant UpPresentationNode::getData(int role, int column)
{
  if (role == Qt::DisplayRole)
  {
    if (column == 0)
    {
      QUrl url = m_item->url();
      if (url.isValid())
      {
        QFileInfo pathInfo(url.path());
        return pathInfo.fileName();
      }
      else
      {
        return "unnamed";
      }
    }
  }
  else if (role == Qt::DecorationRole)
  {
    if (column == 0)
    {
      KMimeType::Ptr mimeType = KMimeType::findByUrl(m_item->url());
      return KIcon(mimeType->iconName());
    }
  }
  return QVariant();
}

int UpPresentationNode::getChildCount() const
{
  return m_item->numSlides();
}

DefaultModelNode* UpPresentationNode::_getChild(int index)
{
  UpSlide* slide = m_item->slide(index);
  assert(0 != slide);
  return new UpSlideNode(this, slide);
}

