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
 * @file KwPlaylistModel.cpp
 * @brief A Qt model for playlist items.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistModel.h"
#include "KwPlaylistNode.h"
#include "KwPlaylistList.h"
#include "KwPlaylistListNode.h"
#include "KwPlaylistSong.h"
#include "KwPlaylistVideo.h"
#include "KwPlaylistImage.h"
#include "KwPlaylistPresentation.h"
#include "KwSongdb.h"

#include "kmimetype.h"

#include <QMimeData>
#include <QUrl>
#include <QStringList>

/*
 * Constructors + destructor.
 */

/// Default constructor.
KwPlaylistModel::KwPlaylistModel(QObject* parent)
: NodeBasedModel<KwPlaylistNode>(parent)
{
}

/// Destructor.
KwPlaylistModel::~KwPlaylistModel()
{
}

/*
 * Drag and drop
 */

QStringList KwPlaylistModel::mimeTypes() const
{
  QStringList mimes;
  mimes << "application/x.kworship.song.list";
  mimes << "text/uri-list";
  return mimes;
}

Qt::DropActions KwPlaylistModel::supportedDropActions() const
{
  return Qt::CopyAction | Qt::MoveAction;
}

Qt::ItemFlags KwPlaylistModel::flags(const QModelIndex& index) const
{
  Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

  KwPlaylistNode* item = itemFromIndex(index);
  if (item != 0)
  {
    defaultFlags = item->getFlags(defaultFlags);
  }

  return defaultFlags;
}

bool KwPlaylistModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
{
  Q_UNUSED(column)

  if (action == Qt::IgnoreAction)
  {
    return true;
  }

  KwPlaylistListNode* list = dynamic_cast<KwPlaylistListNode*>(itemFromIndex(parent));
  if (0 == list)
  {
    return true;
  }
  // Always just append if not given explicit row
  if (row == -1)
  {
    row = list->getChildCount();
  }

  if (data->hasFormat("application/x.kworship.song.list"))
  {
    QByteArray encodedData = data->data("application/x.kworship.song.list");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QStringList newItems;

    while (!stream.atEnd())
    {
      QString text;
      stream >> text;

      QStringList words = text.split(" ");
      if (words[0] == "songdb")
      {
        if (words.size() > 1)
        {
          bool ok;
          int versionId = words[1].toInt(&ok, 0);
          if (ok)
          {
            KwPlaylistSong* newSong = new KwPlaylistSong(KwSongdb::self()->getSongVersionById(versionId));
            beginInsertRows(parent, row, row);
            list->childrenAdded(row, row);
            list->getItem()->addItem(newSong, row);
            endInsertRows();
            ++row;
          }
        }
      }
    }

    return true;
  }
  else if (data->hasUrls())
  {
    QList<QUrl> files = data->urls();
    foreach (QUrl file, files)
    {
      // Get the file's mime type
      KMimeType::Ptr result = KMimeType::findByUrl(KUrl(file));
      KwPlaylistItem* newItem = 0;
      if (!result->isDefault())
      {
        if (result->name().startsWith("image/"))
        {
          newItem = new KwPlaylistImage(file);
        }
        else if (result->name().startsWith("video/"))
        {
          newItem = new KwPlaylistVideo(file);
        }
        // perhaps its a presentation
        /// @todo match against all known presentation mime types
        else if (result->name() == "application/vnd.oasis.opendocument.presentation")
        {
          newItem = new KwPlaylistPresentation(file);
        }
      }
      if (0 == newItem)
      {
        newItem = new KwPlaylistFile(file);
      }
      beginInsertRows(parent, row, row);
      list->childrenAdded(row, row);
      list->getItem()->addItem(newItem, row);
      endInsertRows();
      ++row;
    }

    return true;
  }

  return false;
}

