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
 * @file KwKWorshipFilter.cpp
 * @brief Main KWorship archive load and save filter.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwKWorshipFilter.h"

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwKWorshipFilter::KwKWorshipFilter()
: KwLoadSaveFilter()
{
  m_importMimeTypes += "application/x-kworship+xml";
  m_exportMimeTypes += "application/x-kworship+xml";
  m_importMimeTypes += "application/x-kworship-archive";
  m_exportMimeTypes += "application/x-kworship-archive";
}

/// Destructor.
KwKWorshipFilter::~KwKWorshipFilter()
{
}

/*
 * Main interface
 */

KwDocument* KwKWorshipFilter::load(const QString& filename)
{
  /// @todo Implement KwKWorshipFilter::load
  Q_ASSERT(false);
}

bool KwKWorshipFilter::save(KwDocument* doc, const QString& filename)
{
  /// @todo Implement KwKWorshipFilter::save
  Q_ASSERT(false);
}

/*
 * Virtual interface
 */

void KwKWorshipFilter::v_saveLimitations(KwDocument* doc, Limitations* o_limitations)
{
  /// @todo Implement KwKWorshipFilter::v_saveLimitations
  Q_ASSERT(false);
}
