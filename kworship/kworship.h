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

#ifndef PROTOTYPE2_H
#define PROTOTYPE2_H


#include <kxmlguiwindow.h>

#include "KwLocalDisplayController.h"
#include "KwLocalDisplayPreview.h"

#include "ui_prefs_base.h"

class kworshipView;
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
    void fileNew();
    void optionsPreferences();

private:
    void setupActions();

private:
    Ui::prefs_base ui_prefs_base ;
    kworshipView *m_view;
   
    KwLocalDisplayController m_displayController;
    KwLocalDisplayPreview* m_mainDisplay;
    KwLocalDisplayPreview* m_previewDisplay;

    KPrinter   *m_printer;
    KToggleAction *m_toolbarAction;
    KToggleAction *m_statusbarAction;
};

#endif // _kworship_H_
