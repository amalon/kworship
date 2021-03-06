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

#include <QString>
#include <QStringList>
#include <QList>
#include <QVector>
#include <QHash>

class KwBibleModuleBibleGateway;

/// A bible manager for BibleGateway.com.
class KwBibleManagerBibleGateway : public KwBibleManager
{
    KW_BIBLE_MANAGER(KwBibleManagerBibleGateway, "BibleGateway.com")

  public:
    
    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwBibleManagerBibleGateway(QObject* parent = 0, const QStringList& params = QStringList());

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
    virtual QStringList moduleNames(bool* ok = 0);

    // Reimplemented
    virtual QStringList moduleNamesInLanguage(const QString& lang, bool* ok = 0);

    // Reimplemented
    virtual QStringList languages(bool* ok = 0);

  private:

    /*
     * Private functions
     */

    /// Ensure the version information is cached.
    void ensureCached(bool* ok = 0);

    /// Clear all modules.
    void clear();

    /*
     * Variables
     */

    /// Whether the versions have already been cached.
    bool m_cached;

    /// Language names.
    QStringList m_languages;

    /// Per version data.
    struct Version
    {
      QString name;
      QString url;
      int id;
      int lang;
      KwBibleModuleBibleGateway* module;
    };

    /// Versions by id.
    QVector<Version*> m_versions;

    /// Versions by name.
    QHash<QString, Version*> m_versionsByName;

    /// Version ids by language id.
    QHash<int, QList<int> > m_versionsByLanguage;
};

#endif // _KwBibleManagerBibleGateway_h_

