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
 * @file KwSongdbModel.cpp
 * @brief A Qt model for songs in the database.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbModel.h"

#include <QMimeData>

#include <cassert>

/*
 * Constructors + destructor.
 */

/// Default constructor.
KwSongdbModel::KwSongdbModel(QObject* parent)
: NodeBasedModel<KwSongdbNode>(parent)
{
}

/// Destructor.
KwSongdbModel::~KwSongdbModel()
{
}

/*
 * Drag and drop
 */

Qt::ItemFlags KwSongdbModel::flags(const QModelIndex& index) const
{
  Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

  KwSongdbNode* item = itemFromIndex(index);
  if (0 != item)
  {
    return item->getFlags(defaultFlags);
  }
  else
  {
    return defaultFlags;
  }
}

QMimeData* KwSongdbModel::mimeData(const QModelIndexList& indexes) const
{
  QMimeData *mimeData = new QMimeData();
  QByteArray encodedData;

  QDataStream stream(&encodedData, QIODevice::WriteOnly);

  foreach (QModelIndex index, indexes)
  {
    if (index.isValid())
    {
      KwSongdbNode* item = itemFromIndex(index);
      if (0 != item)
      {
        stream << item->mimeData();
      }
    }
  }

  mimeData->setData("application/x.kworship.song.list", encodedData);
  return mimeData;
}


