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
 * @file KwSongdbTree.h
 * @brief A tree widget with songs from songdb.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbTree.h"
#include "KwSongdbTreeGroupAction.h"
#include "KwSongdbModel.h"
#include "KwSongdbFilterNode.h"

#include <KIcon>

#include <QActionGroup>

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwSongdbTree::KwSongdbTree(QWidget* parent)
: QTreeView(parent)
, m_model(new KwSongdbModel(this))
, m_groupByActions(new QActionGroup(this))
{
  KwSongdbFilterLevelList* filters;

  filters = new KwSongdbFilterLevelList;
  filters->resize(2);
  (*filters)[0].tableName = "`Song`";
  (*filters)[0].idExpression = "`Song`.`id`";
  (*filters)[0].labelExpression = "`Song`.`name`";
  (*filters)[0].orderBy << "`Song`.`name` ASC";
  (*filters)[0].icon = KIcon("view-media-lyrics");
  (*filters)[1].tableName = "`SongVersion`";
  (*filters)[1].idExpression = "`SongVersion`.`id`";
  (*filters)[1].labelExpression = "`SongVersion`.`name`";
  (*filters)[1].innerJoinClauses << "`SongVersion` ON `SongVersion`.`song_id` = `Song`.`id`";
  (*filters)[1].orderBy << "`SongVersion`.`name` ASC";
  (*filters)[1].icon = KIcon("format-list-ordered");
  KwSongdbTreeGroupAction* actionNameVersion = new KwSongdbTreeGroupAction("Song name / Version", filters, m_groupByActions);
  connect(actionNameVersion, SIGNAL(triggered(const KwSongdbFilterLevelList*)), this, SLOT(groupBy(const KwSongdbFilterLevelList*)));

  filters = new KwSongdbFilterLevelList;
  filters->resize(2);
  (*filters)[0].tableName = "`SongBook`";
  (*filters)[0].idExpression = "`SongBook`.`id`";
  (*filters)[0].labelExpression = "CONCAT(`SongBook`.`abreviation`, \" \", `SongBook`.`name`)";
  (*filters)[0].orderBy << "`SongBook`.`name` ASC";
  (*filters)[0].icon = KIcon("bt_book");
  (*filters)[1].tableName = "`SongVersion`";
  (*filters)[1].idExpression = "`SongVersion`.`id`";
  (*filters)[1].labelExpression = "CONCAT(`SongBookSong`.`book_number`, \" - \", `Song`.`name`)";
  (*filters)[1].innerJoinClauses << "`SongBookSong` ON `SongBookSong`.`book_id` = `SongBook`.`id`"
                                 << "`SongVersion` ON `SongVersion`.`id` = `SongBookSong`.`version_id`"
                                 << "`Song` ON `Song`.`id` = `SongVersion`.`song_id`";
  (*filters)[1].orderBy << "`SongBookSong`.`book_number` ASC";
  (*filters)[1].icon = KIcon("view-media-lyrics");
  KwSongdbTreeGroupAction* actionBookNumber = new KwSongdbTreeGroupAction("Song book / Song number", filters, m_groupByActions);
  connect(actionBookNumber, SIGNAL(triggered(const KwSongdbFilterLevelList*)), this, SLOT(groupBy(const KwSongdbFilterLevelList*)));

  filters = new KwSongdbFilterLevelList;
  KwSongdbTreeGroupAction* actionLabelNameVersion = new KwSongdbTreeGroupAction("Label / Song name / Version", filters, m_groupByActions);
  /// @todo implement label filtering
  actionLabelNameVersion->setEnabled(false);
  //connect(actionLabelNameVersion, SIGNAL(triggered(const KwSongdbFilterLevelList*)), this, SLOT(groupBy(const KwSongdbFilterLevelList*)));

  actionNameVersion->trigger();

  // setup tree view
  setModel(m_model);
  setDragEnabled(true);
  setSelectionMode(QAbstractItemView::ExtendedSelection);
}

/// Destructor.
KwSongdbTree::~KwSongdbTree()
{
}

/*
 * Actions
 */

/// Get the group by actions.
QActionGroup* KwSongdbTree::groupByActions()
{
  return m_groupByActions;
}

/*
 * Private slots
 */

/// Activate a grouping.
void KwSongdbTree::groupBy(const KwSongdbFilterLevelList* filters)
{
  m_model->setRootNode(new KwSongdbFilterNode(filters, "", 0));
}

