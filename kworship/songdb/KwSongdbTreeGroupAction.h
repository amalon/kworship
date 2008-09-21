/***************************************************************************
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   This file is part of KWorship.                                        *
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

#ifndef _KwSongdbTreeGroupAction_h_
#define _KwSongdbTreeGroupAction_h_

/**
 * @file KwSongdbTreeGroupAction.h
 * @brief An action for grouping songs in tree.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbFilter.h"

#include <QAction>

/// An action for grouping songs in tree.
class KwSongdbTreeGroupAction : public QAction
{
  Q_OBJECT
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwSongdbTreeGroupAction(QString label, KwSongdbFilterLevelList* filters, QObject* parent = 0);

    /// Destructor.
    virtual ~KwSongdbTreeGroupAction();

  public slots:

    /*
     * Public slots
     */

    /// Trigger new triggered signal.
    void trigger();

  signals:
    
    /*
     * Signals
     */

    /// Action is triggered with a list of filters.
    void triggered(const KwSongdbFilterLevelList* filters);

  private:

    /*
     * Variables
     */

    /// Filter list.
    KwSongdbFilterLevelList* m_filters;

};

#endif // _KwSongdbTreeGroupAction_h_

