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

#ifndef _kworship_h_
#define _kworship_h_

#include "ui_prefsDisplay_base.h"
#include "ui_prefs_base.h"
#include "KwLocalDisplayController.h"

#include <kxmlguiwindow.h>

#include <QModelIndex>

class kworshipView;
class KwLocalDisplay;
class KwLocalDisplayPreview;
class KwDisplayManager;
class KwPlaylistList;
class KwPlaylistModel;
class KwMediaManager;
class KwSongdbModel;

class UpManager;

class KPrinter;
class KToggleAction;
class KUrl;

/**
 * This class serves as the main window for kworship.  It handles the
 * menus, toolbars, and status bars.
 *
 * @short Main window class
 * @author Andreas Pakulat <apaku@gmx.de>
 * @version 0.1
 */
class kworship : public KXmlGuiWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    kworship();

    /**
     * Default Destructor
     */
    virtual ~kworship();

private slots:
    void settingsChanged();
    void toggleMainDisplay(bool checked);
    void mainDisplayClosed();
    void displayClear();
    void fileNew();
    void fileOpen();
    void fileSave();
    void fileSaveAs();
    void toggleFullscreen(bool checked);
    void optionsPreferences();
    void playlist_doubleClicked(QModelIndex);

private:
    void setupActions();
    int getCorrectDisplayScreen();
    int getCurrentDisplayScreen();

private:
    Ui::prefs_base ui_prefs_base ;
    Ui::prefsDisplay_base ui_prefsDisplay_base ;
    kworshipView *m_view;

    KwMediaManager* m_mediaManager;
    KwDisplayManager* m_displayManager;
    KwLocalDisplayController m_displayController;
    KwLocalDisplay* m_mainDisplay;
    KwLocalDisplayPreview* m_previewDisplay;

    KwPlaylistList* m_primaryPlaylist;
    KwPlaylistModel* m_playlistModel;

    KwSongdbModel* m_songDbModel;

    UpManager* m_presentationManager;

    KPrinter   *m_printer;
    KToggleAction* m_mainDisplayAction;
    KToggleAction *m_toolbarAction;
    KToggleAction *m_statusbarAction;
};

#endif // _kworship_h_
