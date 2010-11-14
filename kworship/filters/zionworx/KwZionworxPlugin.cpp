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
 * @file KwZionworxPlugin.cpp
 * @brief Zionworx filters plugin.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwZionworxPlugin.h"
#include "KwZionworxFilter.h"

#include <KwApplication.h>
#include <kworship.h>
#include <KwDocument.h>
#include <KwFilterManager.h>

#include <KLocale>
#include <KGenericFactory>

K_EXPORT_COMPONENT_FACTORY( kworship_zionworx, KGenericFactory<KwZionworxPlugin>("kworship_zionworx") )

/*
 * Constructors + destructor
 */

/// Default constructor.
KwZionworxPlugin::KwZionworxPlugin(QObject* parent, const QStringList& params)
: KwPlugin(parent, "zionworx",
           i18n("Zionworx filters"),
           i18n("The Zionworx filters allow Zionworx playlists to be loaded and saved."))
{
  Q_UNUSED(params);
}

/// Destructor.
KwZionworxPlugin::~KwZionworxPlugin()
{
}

/*
 * Loading and unloading virtual interface
 */

void KwZionworxPlugin::_load()
{
  KwZionworxFilter* filter = new KwZionworxFilter();
  KwApplication::self()->filterManager()->addLoadSaveFilter(filter);
}

void KwZionworxPlugin::_unload()
{
}
