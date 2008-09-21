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
 * @file KwSongdbTreeGroupAction.cpp
 * @brief An action for grouping songs in tree.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbTreeGroupAction.h"
#include "KwSongdbFilter.h"

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwSongdbTreeGroupAction::KwSongdbTreeGroupAction(QString label, KwSongdbFilterLevelList* filters, QObject* parent)
: QAction(label, parent)
, m_filters(filters)
{
  connect(this, SIGNAL(triggered()), this, SLOT(trigger()));
}

/// Destructor.
KwSongdbTreeGroupAction::~KwSongdbTreeGroupAction()
{
  delete m_filters;
}

/*
 * Public slots
 */

/// Trigger new triggered signal.
void KwSongdbTreeGroupAction::trigger()
{
  // Trigger signal
  triggered(m_filters);
}

