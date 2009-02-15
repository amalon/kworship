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

#include "KwZwStringList.h"

#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <kconfigdialogmanager.h>
#include <KDE/KLocale>
#include <KApplication>

int main(int argc, char **argv)
{
  KAboutData about("kworship_zionworx", 0,
                   ki18n("KWorship Zionworx"), "0.1",
                   ki18n("Free/Open source church worship & presentation software"),
                   KAboutData::License_GPL_V2,
                   ki18n("(C) 2008 James Hogan"),
                   KLocalizedString(),
                   "http://kworship.org",
                   "bugs@kworship.org");
  about.addAuthor( ki18n("James Hogan"), KLocalizedString(), "james@albanarts.com" );
  KCmdLineArgs::init(argc, argv, &about);

  KApplication app;

  KwZwStringList* win = new KwZwStringList();
  win->show();

  return app.exec();
}
