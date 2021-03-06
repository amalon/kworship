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

#ifndef _kworship_h_
#define _kworship_h_

#include "ui_prefs_base.h"
#include "ui_prefsDisplay_base.h"
#include "ui_prefsDatabase_base.h"
#include "ui_prefsPresentations_base.h"
#include "KwLocalDisplayController.h"
#include "KwExport.h"

#include <kxmlguiwindow.h>

#include <QModelIndex>

class kworshipView;
class KwLocalDisplay;
class KwLocalDisplayPreview;
class KwDisplayManager;
class KwPlaylistList;
class KwPlaylistModel;
class KwMediaManager;
class KwDocument;
class KwSongdbModel;
class KwSongdbTree;

class UpManager;
class UpPresentation;

class KPrinter;
class KToggleAction;
class KUrl;
class KAction;
class KActionMenu;
class KToggleAction;

class QTreeView;
class QTextEdit;

/**
 * This class serves as the main window for kworship.  It handles the
 * menus, toolbars, and status bars.
 *
 * @short Main window class
 * @author Andreas Pakulat <apaku@gmx.de>
 * @version 0.1
 */
class KWMAIN_EXPORT kworship : public KXmlGuiWindow
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

    /*
     * Public interface
     */

    /// Load a specified playlist.
    void loadPlaylist(const KUrl& url);

    /*
     * Accessors
     */

    /// Get the main display manager.
    KwDisplayManager* displayManager();

    /// Get the current document.
    KwDocument* document();

    /// Get the playlist model.
    KwPlaylistModel* playlistModel();

private slots:
    void settingsChanged();
    void toggleMainDisplay(bool checked);
    void mainDisplayClosed();
    void displayClear();
    bool askToSave();
    void fileNew();
    void fileOpen();
    void fileSave();
    void fileSaveAs();
    void toggleFullscreen(bool checked);
    void optionsPreferences();
    void playlist_clicked(QModelIndex);
    void playlist_doubleClicked(QModelIndex);
    void playlistReset();
    void playlistInsert();
    void playlistDelete();
    void playlistMoveUp();
    void playlistMoveDown();

    /// Add the new docker to the interface.
    void newDocker(QDockWidget* docker);

    void presentationDelete();
    void presentationSelected(int);
    void presentationToggled(bool);
    void presentationPreviousSlide();
    void presentationNextSlide();
    void presentationPreviousStep();
    void presentationNextStep();
    void slide_doubleClicked(QModelIndex);

    // Custom slideshows
    void presentationComboReset();
    void changeSlideshowCombo(QString name);
    void changeSlideshowExternal(QString name);
    void refreshSlideshows();
    void refreshSlides();
    void addSlideshowLinkToPlaylist();
    void addSlideshowCopyToPlaylist();

    // From current presentation
    void slideshowStarted(int numSlides);
    void slideshowStopped();
    void slideshowSlideChanged(int slide, int numSteps);
    void slideshowStepChanged(int step);

private:
    void setupActions();
    int getCorrectDisplayScreen();
    int getCurrentDisplayScreen();

    // Documents
    void clearDocument();
    // Presentations
    void setPresentation(UpPresentation* presentation, bool alreadyDestroyed = false);

private:
    Ui::prefs_base ui_prefs_base ;
    Ui::prefsPresentations_base ui_prefsPresentations_base ;
    kworshipView *m_view;

    KwMediaManager* m_mediaManager;
    KwDisplayManager* m_displayManager;
    KwLocalDisplayController m_displayController;
    KwLocalDisplay* m_mainDisplay;
    KwLocalDisplayPreview* m_previewDisplay;

    KwDocument* m_document;
    KwPlaylistModel* m_playlistModel;
    KAction* m_playlistInsertAction;
    KAction* m_playlistDeleteAction;
    KAction* m_playlistMoveUpAction;
    KAction* m_playlistMoveDownAction;

    UpManager* m_presentationManager;
    QTreeView* m_selectPresTree;
    QTextEdit* m_slideNotes;
    KAction* m_slideshowPrevSlideAction;
    KAction* m_slideshowPrevStepAction;
    KAction* m_slideshowNextStepAction;
    KAction* m_slideshowNextSlideAction;
    KToggleAction* m_slideshowAction;
    UpPresentation* m_currentPresentation;

    KPrinter   *m_printer;
    KToggleAction* m_mainDisplayAction;
    KToggleAction *m_toolbarAction;
    KToggleAction *m_statusbarAction;
};

#endif // _kworship_h_
