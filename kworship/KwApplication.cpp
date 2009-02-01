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
 * @file KwApplication.cpp
 * @brief Application global data.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwApplication.h"
#include "kworship.h"
#include "KwPluginManager.h"

#include <KCmdLineArgs>

/*
 * Static singleton data
 */

/// Singleton application.
KwApplication* KwApplication::s_self = 0;

/*
 * Singletonhood
 */

/// Get the singleton application object.
KwApplication* KwApplication::self()
{
  return s_self;
}

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwApplication::KwApplication()
: m_app()
, m_mainWindow(0) // soon to be initialised
, m_pluginManager(new KwPluginManager())
{
  // Application must be lone.
  Q_ASSERT(0 == s_self);
  s_self = this;

  // Set up the main window
  kworship *widget = new kworship;
  m_mainWindow = widget;

  // Set up the plugin manager
  m_pluginManager->setMainWindow(m_mainWindow);
  m_pluginManager->loadPlugins();

  // see if we are starting with session management
  if (m_app.isSessionRestored())
  {
    RESTORE(kworship);
  }
  else
  {
    widget->show();
    // no session.. just start up normally
    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
    if (args->count() > 0)
    {
      KUrl arg = args->arg(0);
      KUrl url = KCmdLineArgs::cwd();
      if (arg.isRelative())
      {
        url.addPath(arg.path());
      }
      else
      {
        url = arg;
      }
      widget->loadPlaylist(url);
    }
    args->clear();
  }
}

/// Destructor.
KwApplication::~KwApplication()
{
  Q_ASSERT(this == s_self);
  s_self = 0;

  delete m_pluginManager;
}

/*
 * Main interface
 */

/// Execute the application.
int KwApplication::exec()
{
  return m_app.exec();
}

/*
 * Accessors
 */

/// Get the main window widget.
kworship* KwApplication::mainWindow()
{
  return m_mainWindow;
}

