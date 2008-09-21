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
 * @file KwMediaControlWidgetVisual.cpp
 * @brief Controls visual preferences of playing media items.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwMediaControlWidgetVisual.h"

#include <QVBoxLayout>
#include <QSlider>

/*
 * Constructors + destructors
 */

/// Primary constructor.
KwMediaControlWidgetVisual::KwMediaControlWidgetVisual(KwMediaManager* manager, QWidget* parent)
: QWidget(parent)
, m_manager(manager)
{
  QVBoxLayout* layout = new QVBoxLayout;
  layout->setContentsMargins(0, 0, 0, 0);
  setLayout(layout);
}

/// Destructor.
KwMediaControlWidgetVisual::~KwMediaControlWidgetVisual()
{
}

