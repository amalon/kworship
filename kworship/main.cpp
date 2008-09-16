/***************************************************************************
 *   Copyright (C) 2008 by James Hogan   *
 *   james@albanarts.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "kworship.h"

#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <kconfigdialogmanager.h>
#include <KDE/KLocale>

static const char description[] =
    I18N_NOOP("A KDE 4 Application");

static const char version[] = "0.1";

int main(int argc, char **argv)
{
    KAboutData about("kworship", 0, ki18n("kworship"), version, ki18n(description),
                     KAboutData::License_GPL, ki18n("(C) 2008 James Hogan"), KLocalizedString(), 0, "james@albanarts.com");
    about.addAuthor( ki18n("James Hogan"), KLocalizedString(), "james@albanarts.com" );
    KCmdLineArgs::init(argc, argv, &about);

    KCmdLineOptions options;
    options.add("+[URL]", ki18n( "Document to open" ));
    KCmdLineArgs::addCmdLineOptions(options);
    KApplication app;

    // Screen number can be managed by a DesktopView widget
    KConfigDialogManager::changedMap()->insert("DesktopView", SIGNAL(screenChanged(int)));
    KConfigDialogManager::propertyMap()->insert("DesktopView", "selectedScreen");

    kworship *widget = new kworship;

    // see if we are starting with session management
    if (app.isSessionRestored())
    {
        RESTORE(kworship);
    }
    else
    {
        // no session.. just start up normally
        KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
        if (args->count() == 0)
        {
            //kworship *widget = new kworship;
            widget->show();
        }
        else
        {
            int i = 0;
            for (; i < args->count(); i++)
            {
                //kworship *widget = new kworship;
                widget->show();
            }
        }
        args->clear();
    }

    return app.exec();
}
