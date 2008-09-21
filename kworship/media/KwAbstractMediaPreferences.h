/***************************************************************************
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   This file is part of KWorship.                                        *
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

#ifndef _KwAbstractMediaPreferences_h_
#define _KwAbstractMediaPreferences_h_

/**
 * @file KwAbstractMediaPreferences.h
 * @brief A media item's preferences.
 * @author James Hogan <james@albanarts.com>
 */

#include <QObject>

class KwMediaManager;

/// A media item's preferences.
/**
 * To allow live updating of outputs.
 */
class KwAbstractMediaPreferences : public QObject
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwAbstractMediaPreferences();

    /// Destructor.
    virtual ~KwAbstractMediaPreferences();

    /*
     * Main interface
     */

    /// Set the manager.
    void setManager(KwMediaManager* manager);

  private:

    /*
     * Variables
     */

    /// Manager to control.
    KwMediaManager* m_manager;

};

#endif // _KwAbstractMediaPreferences_h_

