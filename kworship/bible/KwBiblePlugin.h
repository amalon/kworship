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

#ifndef _KwBiblePlugin_h_
#define _KwBiblePlugin_h_

/**
 * @file KwBiblePlugin.h
 * @brief Bibles plugin.
 * @author James Hogan <james@albanarts.com>
 */

#include <KwPlugin.h>

#include "KwBibleModule.h"

class KwBibleManager;

class KAction;

class QDockWidget;
class QTabWidget;
class QComboBox;
class QLineEdit;
class QTextEdit;
class QToolBar;

/// Bibles plugin.
class KwBiblePlugin : public KwPlugin
{
    Q_OBJECT

  public:

    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwBiblePlugin(QObject* parent = 0, const QStringList& params = QStringList());

    /// Destructor.
    virtual ~KwBiblePlugin();

    /*
     * Accessors
     */

    /// Get the current bible passage information.
    bool resolvePassage(KwBibleManager** manager, KwBibleModule** module, KwBibleModule::Key* key, bool* usedSearch = 0) const;

  private slots:

    /*
     * Private slots
     */

    /// Fired when the connect to bible button is pressed.
    void slotConnect();

    /// Fired when the bible is changed.
    void slotBibleChanged();

    /// Fired when the bible book is changed.
    void slotBookChanged();

    /// Fired when the bible text needs to be retrieved.
    void slotVerseRange();

    /// Fired by the insert into playlist action.
    void slotInsertIntoPlaylist();

    /// Fired by the show now action.
    void slotShowNow();

  protected:

    /*
     * Loading and unloading virtual interface
     */

    // Reimplemented
    virtual void _load();

    // Reimplemented
    virtual void _unload();

  private:

    /*
     * Types
     */

    struct BibleManager
    {
      KwBibleManager* manager;
      QComboBox* comboBibles;
      QToolBar* toolBar;
    };

    /*
     * Private functions
     */

    /// Fill up the bibles list for a manager.
    void fillBiblesList(BibleManager* mgr);

    /*
     * Variables
     */

    /// The list of bible managers.
    QList<BibleManager> m_managers;

    /*
     * Actions
     */

    /// Action for inserting the current passage into the playlist.
    KAction* m_insertIntoPlaylistAction;

    /// Action for showing the current passage on the screen.
    KAction* m_showNowAction;

    /*
     * Widgets
     */

    /// Bible docker.
    QDockWidget* m_docker;

    /// Tabs for each bible manager.
    QTabWidget* m_managerTabs;

    /// Book of bible selector.
    QComboBox* m_comboBook;

    /// Chapter of bible book selector.
    QComboBox* m_comboChapter;

    /// Verse range box.
    QLineEdit* m_editRange;

    /// Main bible text display.
    QTextEdit* m_textPassage;
};

#endif // _KwBiblePlugin_h_

