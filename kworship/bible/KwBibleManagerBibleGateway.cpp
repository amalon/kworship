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

/**
 * @file KwBibleManagerBibleGateway.cpp
 * @brief A bible manager for BibleGateway.com.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBibleManagerBibleGateway.h"
#include "KwBibleModuleBibleGateway.h"

#include <KIO/NetAccess>
#include <KMessageBox>

#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNodeList>

KW_REGISTER_BIBLE_MANAGER(KwBibleManagerBibleGateway)

/*
 * Constructors + destructor
 */

/// Default constructor.
KwBibleManagerBibleGateway::KwBibleManagerBibleGateway()
: KwBibleManager()
, m_cached(false)
, m_languages()
, m_versionsById()
, m_versionsByName()
, m_versionsByLanguage()
{
}

/// Destructor.
KwBibleManagerBibleGateway::~KwBibleManagerBibleGateway()
{
  foreach (Version* version, m_versionsById)
  {
    delete version->module;
    delete version;
  }
}

/*
 * Main interface
 */

QString KwBibleManagerBibleGateway::name() const
{
  return "BibleGateway.com";
}

bool KwBibleManagerBibleGateway::isRemote() const
{
  return true;
}

KwBibleModule* KwBibleManagerBibleGateway::module(const QString& name)
{
  QHash<QString, Version*>::iterator it = m_versionsByName.find(name);
  Version* version = 0;
  // Does the module with this name exist?
  if (it != m_versionsByName.end())
  {
    version = *it;
  }
  // Otherwise perhaps its a language
  else
  {
    int langId = m_languages.indexOf(name);
    if (-1 != langId)
    {
      // Just get the first module of this language
      const QList<int>& moduleIds = m_versionsByLanguage[langId];
      if (!moduleIds.isEmpty())
      {
        int id = moduleIds.first();
        version = m_versionsById[id];
      }
    }
  }
  if (0 != version)
  {
    if (0 == version->module)
    {
      version->module = new KwBibleModuleBibleGateway(version->id);
    }
    return version->module;
  }
  else
  {
    return 0;
  }
}

QStringList KwBibleManagerBibleGateway::moduleNames()
{
  ensureCached();
  return m_versionsByName.keys();
}

QStringList KwBibleManagerBibleGateway::moduleNamesInLanguage(const QString& lang)
{
  ensureCached();
  int languageId = m_languages.indexOf(lang);
  QStringList names;
  if (languageId >= 0)
  {
    const QList<int>& moduleIds = m_versionsByLanguage[languageId];
    foreach (int id, moduleIds)
    {
      names << m_versionsById[id]->name;
    }
  }
  return names;
}

QStringList KwBibleManagerBibleGateway::languages()
{
  ensureCached();
  return m_languages;
}

/*
 * Private functions
 */

/// Ensure the version information is cached.
void KwBibleManagerBibleGateway::ensureCached()
{
  if (!m_cached)
  {
    QString tmpFile;
    if (KIO::NetAccess::download(KUrl("http://www.biblegateway.com/"), tmpFile, 0))
    {
      QFile file(tmpFile);
      if (file.open(QFile::ReadOnly | QFile::Text))
      {
        QByteArray rawPage = file.readAll();
        file.close();
        /// @todo Convert to use KDE DOM as its a bit more flexible of invalid XML
        QString page = QString::fromUtf8(rawPage);
        QRegExp rx("<select\\s+name=\"qs_version\">.*</select>");
        if (-1 != rx.indexIn(page))
        {
          QDomDocument dom;
          if (dom.setContent(rx.cap(), false))
          {
            // Go through all the options (languages and versions)
            int langId = -1;
            QList<int>* langMods = 0;
            QDomNodeList options = dom.elementsByTagName("option");
            for (int i = 0; i < options.count(); ++i)
            {
              QDomElement el = options.at(i).toElement();
              if (!el.isNull())
              {
                // Its either a language (with class="lang") or a version
                QString className = el.attribute("class");
                QString text = el.text();
                if (className == "lang")
                {
                  m_languages << text;
                  ++langId;
                  langMods = &m_versionsByLanguage[langId];
                }
                else if (langId >= 0)
                {
                  bool ok;
                  int versionId = el.attribute("value").toInt(&ok);
                  if (ok)
                  {
                    // Ensure there is none with this id already
                    QHash<int, Version*>::const_iterator it = m_versionsById.constFind(versionId);
                    if (it == m_versionsById.constEnd())
                    {
                      Version* version = new Version;
                      version->name = text;
                      version->id = versionId;
                      version->module = 0;
                      m_versionsById[versionId] = version;
                      m_versionsByName[text] = version;
                      *langMods << versionId;
                    }
                  }
                }
              }
            }
            m_cached = true;
          }
        }
      }

      KIO::NetAccess::removeTempFile(tmpFile);
    }
    else
    {
      KMessageBox::error(0, KIO::NetAccess::lastErrorString());
    }
  }
}

/// Clear all modules.
void KwBibleManagerBibleGateway::clear()
{
  if (m_cached)
  {
    foreach (Version* version, m_versionsById)
    {
      delete version->module;
      delete version;
    }
    m_cached = false;
    m_languages.clear();
    m_versionsById.clear();
    m_versionsByName.clear();
    m_versionsByLanguage.clear();
  }
}

