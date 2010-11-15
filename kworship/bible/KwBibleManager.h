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

#ifndef _KwBibleManager_h_
#define _KwBibleManager_h_

/**
 * @file KwBibleManager.h
 * @brief A bible manager (analagous to a SWORD manager).
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBibleExport.h"

#include <Factory.h>

#include <QObject>
#include <QStringList>
#include <QString>
#include <QList>
#include <QMap>

class KwBibleModule;

#define KW_BIBLE_MANAGER(X, KEY) \
  private: \
    /* \
     * Static private variables \
     */ \
    static bool s_registered; \
  public: \
    static void registerManager() \
    { \
      if (!s_registered) \
      { \
        s_registered = KwBibleManager::factory()->addType< X >(KEY); \
      } \
    }

#define KW_REGISTER_BIBLE_MANAGER(X) \
  bool X::s_registered = false;

/// A bible manager (analagous to a SWORD manager).
class KWBIBLE_EXPORT KwBibleManager : public QObject
{
    Q_OBJECT

  public:

    /*
     * Manager factory
     */

    /// Factory of managers identified by strings.
    typedef ::Factory<QString, KwBibleManager, META_TUPLE(())> Factory;

    /// Get a factory object.
    static Factory* factory();

    /// Get a singleton for a manager.
    static KwBibleManager* singleton(const QString& key);
    
    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwBibleManager(QObject* parent = 0, const QStringList& params = QStringList());

    /// Destructor.
    virtual ~KwBibleManager();

    /*
     * Main interface
     */

    /// Get the name of the manager.
    virtual QString name() const = 0;

    /** Get whether the manager is remote.
     * This means the modules should not be accessed unless they are requested
     * explicitly by the user.
     */
    virtual bool isRemote() const = 0;

    /// Get a module by name.
    virtual KwBibleModule* module(const QString& name) = 0;

    /// Get the list of module names.
    virtual QStringList moduleNames(bool* ok = 0) = 0;

    /// Get the list of module names in a specific language.
    virtual QStringList moduleNamesInLanguage(const QString& lang, bool* ok = 0) = 0;

    /// Get a list of module languages.
    virtual QStringList languages(bool* ok = 0) = 0;
};

#endif // _KwBibleManager_h_

