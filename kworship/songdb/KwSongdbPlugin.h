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

#ifndef _KwSongdbPlugin_h_
#define _KwSongdbPlugin_h_

/**
 * @file KwSongdbPlugin.h
 * @brief Song database plugin.
 * @author James Hogan <james@albanarts.com>
 */

#include <KwPlugin.h>

class KwSongdbTree;
class KActionMenu;

/// Song database plugin.
class KwSongdbPlugin : public KwPlugin
{
    Q_OBJECT

  public:

    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwSongdbPlugin(QObject* parent = 0, const QStringList& params = QStringList());

    /// Destructor.
    virtual ~KwSongdbPlugin();

  private slots:

    /*
     * Slots
     */

    void songdbUnlock();
    void songdbLock();
    void songdbAdd();
    void songdbEdit();
    void songdbEditSongBooks();

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
     * Variables
     */

    /// Song DB docker.
    QDockWidget* m_docker;

    KwSongdbTree* m_songDbTree;
    KAction* m_unlockSongDbAction;
    KAction* m_lockSongDbAction;
    KActionMenu* m_groupSongsByAction;
    KAction* m_addSongAction;
    KAction* m_editSongAction;
    KAction* m_editSongBooksAction;
};

#endif // _KwSongdbPlugin_h_

