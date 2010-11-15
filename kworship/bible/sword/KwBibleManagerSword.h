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

#ifndef _KwBibleManagerSword_h_
#define _KwBibleManagerSword_h_

/**
 * @file KwBibleManagerSword.h
 * @brief A bible manager for SWORD.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBibleManager.h"

#include <QHash>
#include <QStringList>

namespace sword
{
  class SWMgr;
}

/// A bible manager (analagous to a SWORD manager).
class KwBibleManagerSword : public KwBibleManager
{
    KW_BIBLE_MANAGER(KwBibleManagerSword, "SWORD");

  public:
    
    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwBibleManagerSword(QObject* parent = 0, const QStringList& params = QStringList());

    /// Destructor.
    virtual ~KwBibleManagerSword();

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
    virtual QStringList moduleNames(bool* ok = 0);

    // Reimplemented
    virtual QStringList moduleNamesInLanguage(const QString& lang, bool* ok = 0);

    // Reimplemented
    virtual QStringList languages(bool* ok = 0);

  private:

    /*
     * Variables
     */

    /// SWORD manager object.
    sword::SWMgr* m_manager;

    /// Modules managed by this manager.
    QHash<QString, KwBibleModule*> m_modules;

    /// Languages.
    QStringList m_languages;

    /// Modules by language.
    QHash<QString, QStringList> m_modulesByLanguage;
};

#endif // _KwBibleManagerSword_h_

