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

#ifndef _KwSongdbTree_h_
#define _KwSongdbTree_h_

/**
 * @file KwSongdbTree.h
 * @brief A tree widget with songs from songdb.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbFilter.h"

#include <QTreeView>

class KwSongdbModel;
class QActionGroup;

/// A tree widget with songs from songdb.
class KwSongdbTree : public QTreeView
{
  Q_OBJECT
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwSongdbTree(QWidget* parent = 0);

    /// Destructor.
    virtual ~KwSongdbTree();

    /*
     * Actions
     */

    /// Get the group by actions.
    QActionGroup* groupByActions();

  private slots:

    /*
     * Private slots
     */

    /// Activate a grouping.
    void groupBy(const KwSongdbFilterLevelList* filters);


  private:

    /*
     * Variables
     */

    /// Model.
    KwSongdbModel* m_model;

    /// Group by actions.
    QActionGroup* m_groupByActions;

    /// 
};

#endif // _KwSongdbTree_h_

