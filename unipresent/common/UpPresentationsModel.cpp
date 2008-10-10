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
 * @file UpPresentationsModel.cpp
 * @brief A Qt model for presentation items.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpPresentationsModel.h"
#include "UpPresentation.h"
#include "UpManagerNode.h"
#include "UpBackendNode.h"
#include "UpPresentationNode.h"

/*
 * Constructors + destructor
 */

/// Default constructor.
UpPresentationsModel::UpPresentationsModel(QObject* parent)
: NodeBasedModel<>(parent)
{
}

/// Destructor.
UpPresentationsModel::~UpPresentationsModel()
{
}

/*
 * Public slots
 */

void UpPresentationsModel::loadedPresentation(UpPresentation* presentation)
{
  // First find the backend
  UpManagerNode* root = dynamic_cast<UpManagerNode*>(getRootNode());
  Q_ASSERT(0 != root);
  UpBackendNode* backendNode = root->getBackendNode(presentation->backend());
  if (0 != backendNode)
  {
    int backendRow = root->getChildIndex(backendNode);
    Q_ASSERT(-1 != backendRow);
    QModelIndex backendIndex = index(backendRow, 0, QModelIndex());
    int row = backendNode->getChildCount() - 1;
    beginInsertRows(backendIndex, row, row);
    backendNode->childrenAdded(row, row);
    endInsertRows();
  }
}

void UpPresentationsModel::unloadedPresentation(UpPresentation* presentation)
{
  // First find the backend
  UpManagerNode* root = dynamic_cast<UpManagerNode*>(getRootNode());
  Q_ASSERT(0 != root);
  UpBackendNode* backendNode = root->getBackendNode(presentation->backend());
  if (0 != backendNode)
  {
    // Now find the presentation node
    UpPresentationNode* presentationNode = backendNode->getPresentationNode(presentation);
    if (0 != presentationNode)
    {
      int row = backendNode->getChildIndex(presentationNode);
      if (row != -1)
      {
        int backendRow = root->getChildIndex(backendNode);
        Q_ASSERT(-1 != backendRow);
        QModelIndex backendIndex = index(backendRow, 0, QModelIndex());
        beginRemoveRows(backendIndex, row, row);
        backendNode->childrenRemoved(row, row);
        endRemoveRows();
      }
    }
  }
}

