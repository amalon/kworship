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
#include <KGenericFactory>

#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNodeList>

KW_REGISTER_BIBLE_MANAGER(KwBibleManagerBibleGateway)

K_EXPORT_COMPONENT_FACTORY( kworship_bible_biblegateway, KGenericFactory<KwBibleManagerBibleGateway>("kworship_bible_biblegateway") )

/*
 * Constructors + destructor
 */

/// Default constructor.
KwBibleManagerBibleGateway::KwBibleManagerBibleGateway(QObject* parent, const QStringList& params)
: KwBibleManager(parent, params)
, m_cached(false)
, m_languages()
, m_versions()
, m_versionsByName()
, m_versionsByLanguage()
{
  registerManager();
}

/// Destructor.
KwBibleManagerBibleGateway::~KwBibleManagerBibleGateway()
{
  foreach (Version* version, m_versions)
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
        version = m_versions[id];
      }
    }
  }
  if (0 != version)
  {
    if (0 == version->module)
    {
      version->module = new KwBibleModuleBibleGateway(version->url);
    }
    return version->module;
  }
  else
  {
    return 0;
  }
}

QStringList KwBibleManagerBibleGateway::moduleNames(bool* ok)
{
  ensureCached(ok);
  return m_versionsByName.keys();
}

QStringList KwBibleManagerBibleGateway::moduleNamesInLanguage(const QString& lang, bool* ok)
{
  ensureCached(ok);
  int languageId = m_languages.indexOf(lang);
  QStringList names;
  if (languageId >= 0)
  {
    const QList<int>& moduleIds = m_versionsByLanguage[languageId];
    foreach (int id, moduleIds)
    {
      names << m_versions[id]->name;
    }
  }
  return names;
}

QStringList KwBibleManagerBibleGateway::languages(bool* ok)
{
  ensureCached(ok);
  return m_languages;
}

/*
 * Private functions
 */

/// Ensure the version information is cached.
void KwBibleManagerBibleGateway::ensureCached(bool* ok)
{
  if (!m_cached)
  {
    QString tmpFile;
    // First get list from drop down menu on main page
#if 0
    if (KIO::NetAccess::download(KUrl("http://mobile.biblegateway.com/"), tmpFile, 0))
    {
      QFile file(tmpFile);
      if (file.open(QFile::ReadOnly | QFile::Text))
      {
        QByteArray rawPage = file.readAll();
        file.close();
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
                  QString versionId = el.attribute("value");
                  // Ensure there is none with this shortname already
                  QHash<QString, Version*>::const_iterator it = m_versionsByShortName.constFind(versionId);
                  if (it == m_versionsByShortName.constEnd())
                  {
                    Version* version = new Version;
                    version->name = text;
                    version->shortname = versionId;
                    version->id = m_versionsById.size();
                    version->module = 0;
                    m_versionsById[version->id] = version;
                    m_versionsByName[text] = version;
                    m_versionsByShortName[versionId] = version;
                    *langMods << version->id;
                  }
                }
              }
            }
          }
        }
      }
    }
#endif
    if (KIO::NetAccess::download(KUrl("http://mobile.biblegateway.com/versions"), tmpFile, 0))
    {
      QFile file(tmpFile);
      if (file.open(QFile::ReadOnly | QFile::Text))
      {
        QByteArray rawPage = file.readAll();
        file.close();
        QString page = QString::fromUtf8(rawPage);
        QRegExp rx("<table[^>]*class=\"infotable\">.*</table>");
        if (-1 != rx.indexIn(page))
        {
          QDomDocument dom;
          if (dom.setContent(rx.cap(), false))
          {
            // Go through all the options (languages and versions)
            int langId = -1;
            int rowSpan = 0;
            QList<int>* langMods = 0;
            QDomNodeList rows = dom.elementsByTagName("tr");
            for (int i = 0; i < rows.count(); ++i)
            {
              QDomElement row = rows.at(i).toElement();
              if (!row.isNull())
              {
                QDomNodeList cols = row.elementsByTagName("td");
                for (int j = 0; j < cols.count(); ++j)
                {
                  QDomElement cell = cols.at(j).toElement();
                  if (!cell.isNull())
                  {
                    // if first columnn and rowspan, its a language
                    QString rowSpanStr = cell.attribute("rowspan");
                    bool ok;
                    int newRowSpan = rowSpanStr.toInt(&ok);
                    if (!j && ok && newRowSpan)
                    {
                      QString text = cell.text();
                      m_languages << text;
                      ++langId;
                      langMods = &m_versionsByLanguage[langId];
                      rowSpan = newRowSpan;
                    }
                    else if (langId >= 0)
                    {
                      QDomNodeList as = cell.elementsByTagName("a");
                      if (as.count())
                      {
                        QDomElement ael = as.at(0).toElement();
                        if (!ael.isNull())
                        {
                          QString href = ael.attribute("href");
                          QString text = ael.text();
                          QHash<QString, Version*>::const_iterator it = m_versionsByName.constFind(text);
                          if (it == m_versionsByName.constEnd())
                          {
                            Version* version = new Version;
                            version->name = text;
                            version->id = m_versions.size();
                            version->module = 0;
                            version->url = href;
                            m_versions.push_back(version);
                            m_versionsByName[text] = version;
                            *langMods << version->id;
                          }
                        }
                      }
                      // jump out of column loop
                      break;
                    }
                  }
                }
                if (rowSpan)
                  --rowSpan;
              }
            }
            m_cached = true;
          }
        }
      }

      if (ok)
        *ok = true;
      KIO::NetAccess::removeTempFile(tmpFile);
    }
    else
    {
      if (ok)
        *ok = false;
      KMessageBox::error(0, KIO::NetAccess::lastErrorString());
    }
  }
  else if (ok)
  {
    *ok = true;
  }
}

/// Clear all modules.
void KwBibleManagerBibleGateway::clear()
{
  if (m_cached)
  {
    foreach (Version* version, m_versions)
    {
      delete version->module;
      delete version;
    }
    m_cached = false;
    m_languages.clear();
    m_versions.clear();
    m_versionsByName.clear();
    m_versionsByLanguage.clear();
  }
}

