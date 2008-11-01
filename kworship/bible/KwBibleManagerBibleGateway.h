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

#ifndef _KwBibleManagerBibleGateway_h_
#define _KwBibleManagerBibleGateway_h_

/**
 * @file KwBibleManagerBibleGateway.h
 * @brief A bible manager for BibleGateway.com.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBibleManager.h"

#include <QStringList>

/// A bible manager for BibleGateway.com.
class KwBibleManagerBibleGateway : public KwBibleManager
{
  public:
    
    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwBibleManagerBibleGateway();

    /// Destructor.
    virtual ~KwBibleManagerBibleGateway();

    /*
     * Main interface
     */

    // Reimplemented
    virtual QString name() const;

    // Reimplemented
    virtual bool isRemote() const;

    // Reimplemented
    virtual KwBibleModule* module(const QString& name);

    // Reimplemented
    virtual QStringList moduleNames();

    // Reimplemented
    virtual QStringList moduleNamesInLanguage(const QString& lang);

    // Reimplemented
    virtual QStringList languages();

  private:

    /*
     * Variables
     */

    /// Cached module names.
    QStringList m_moduleNames;

    /// Modules managed by this manager.
    QMap<QString, KwBibleModule*> m_modules;
};

#endif // _KwBibleManagerBibleGateway_h_

