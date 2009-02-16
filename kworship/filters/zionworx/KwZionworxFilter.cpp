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
 * @file KwZionworxFilter.cpp
 * @brief Main Zionworx load and save filter.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwZionworxFilter.h"
#include "KwPascalStream.h"
#include <KwDocument.h>
#include <KwArchive.h>
#include <KwPlaylistList.h>
#include <KwPlaylistText.h>

#include <VTable.h>

#include <KUrl>
#include <KMessageBox>
#include <KLocale>
#include <KSaveFile>

#include <QFile>
#include <QDomDocument>
#include <QDomElement>

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwZionworxFilter::KwZionworxFilter()
: KwLoadSaveFilter()
{
  m_importMimeTypes += "application/x-zionworx+xml";
  m_exportMimeTypes += "application/x-zionworx+xml";
}

/// Destructor.
KwZionworxFilter::~KwZionworxFilter()
{
}

/*
 * Main interface
 */

KwDocument* KwZionworxFilter::load(const KUrl& url, const QString& mimeType)
{
  /// @todo Handle non-local files
  if (!url.isLocalFile())
  {
    KMessageBox::error(0,
        i18n("Non-local loads not yet supported"),
        i18n("KWorship"));
    return 0;
  }

  KwDocument* doc = 0;

  if (mimeType == "application/x-zionworx+xml")
  {
    QFile file(url.toLocalFile());
    if (file.open(QIODevice::ReadOnly))
    {
      QDomDocument domDoc;
      if (domDoc.setContent(&file))
      {
        QDomElement root = domDoc.documentElement();
        QDomElement versionEl = root.firstChildElement("ZionWorx");
        if (root.tagName() != "Root" || versionEl.isNull())
        {
          KMessageBox::error(0,
              i18n("Doesn't look like a ZionWorx playlist"),
              i18n("KWorship"));
        }
        else
        {
          bool versionOk = false;
          double version = versionEl.attribute("Version").toDouble(&versionOk);
          if (!versionOk || version != 2.6)
          {
            KMessageBox::error(0,
                i18n("Only version 2.6 is supported (version is %1)").arg(versionEl.attribute("Version", "unspecified")),
                i18n("KWorship"));
          }
          else
          {
            doc = new KwDocument(this, mimeType, url);
            KwPlaylistList* list = new KwPlaylistList();
            doc->setPlaylist(list);

            QDomNodeList playlistNodes = root.elementsByTagName("TPlayListNode");
            for (int i = 0; i < playlistNodes.count(); ++i)
            {
              QDomElement playlistNode = playlistNodes.at(i).toElement();
              QDomElement item = playlistNode.firstChildElement("PlayListItem");
              if (!item.isNull())
              {
                QString itemType = item.firstChildElement("ItemType").text();
                if (itemType == "siPowerPoint")
                {
                  KwPlaylistText* powerpoint = new KwPlaylistText(item.firstChildElement("Title").text(),
                                                                  QStringList());
                  list->addItem(powerpoint);
                }
                else if (itemType == "siSong")
                {
                  KwPlaylistText* song = new KwPlaylistText(item.firstChildElement("Title").text(),
                                                            item.firstChildElement("Lyrics").text().split("\n\n"));
                  list->addItem(song);
                }
                else if (itemType == "siQuickNote")
                {
                  KwPlaylistText* note = new KwPlaylistText(item.firstChildElement("Title").text(),
                                                            readStringList(item.firstChildElement("QuickNote")));
                  list->addItem(note);
                }
                else if (itemType == "siBible")
                {
                  KwPlaylistText* bible = new KwPlaylistText(item.firstChildElement("Title").text(),
                                                             readStringList(item.firstChildElement("Verses")));
                  list->addItem(bible);
                }
                else
                {
                  KMessageBox::error(0,
                      i18n("Unrecognised item type \"%1\"").arg(itemType),
                      i18n("KWorship"));
                }
              }
            }

            doc->setModified(false);
          }
        }
      }
      else
      {
        KMessageBox::error(0,
            i18n("Invalid XML"),
            i18n("KWorship"));
      }
    }
  }
  else
  {
    Q_ASSERT(!"Unsupported mime type");
  }

  return doc;
}

bool KwZionworxFilter::save(KwDocument* doc, const KUrl& url, const QString& mimeType)
{
  /// @todo Handle non-local files
  if (!url.isLocalFile())
  {
    KMessageBox::error(0,
        i18n("Non-local loads not yet supported"),
        i18n("KWorship"));
    return false;
  }
  KSaveFile file;
  file.setFileName(url.toLocalFile());
  if (!file.open(QFile::WriteOnly))
  {
    KMessageBox::error(0,
        i18n("Cannot write file %1:\n%2.")
          .arg(file.fileName())
          .arg(file.errorString()),
        i18n("KWorship"));
    return false;
  }

  /// @todo Implement KwZionworxFilter::save
  file.abort();
  return false;

  if (!file.finalize())
  {
    KMessageBox::error(0,
        i18n("Cannot finalize file %1:\n%2.")
        .arg(file.fileName())
        .arg(file.errorString()),
        i18n("KWorship"));
    return false;
  }

  doc->setModified(false);

  return true;
}

/*
 * Virtual interface
 */

void KwZionworxFilter::v_saveLimitations(KwDocument* doc, const QString& mimeType, Limitations* o_limitations)
{
  /// @todo Implement KwZionworxFilter::v_saveLimitations
  Q_ASSERT(false);
}

/*
 * Private functions
 */

/// Read a TTntStringList from DOM.
QStringList KwZionworxFilter::readStringList(const QDomElement& el) const
{
  // Go straight to the <DefinedProperties>
  QDomElement definedProperties = el.firstChildElement("DefinedProperties");
  if (!definedProperties.isNull())
  {
    const QByteArray buf = QByteArray::fromBase64(definedProperties.text().toAscii());

    KwPascalStream stream(&buf);
    QByteArray name;
    QVariant value;
    while (!stream.atEnd())
    {
      stream.readProperty(name, value);
      if (name == "Strings")
      {
        // Turn into a QStringList
        QStringList result;
        foreach (QVariant item, value.toList())
        {
          result += item.toString();
        }
        return result;
      }
    }
  }
  return QStringList();
}

/*
 * Static functions
 */

/*
namespace exportToDom
{
  int list(const KwPlaylistList* self, QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager)
  {
    self->exportToDom(document, element, resourceManager);
  }
}

/// Export a playlist item to a DOM.
void KwDataFile::exportToDom(const KwPlaylistItem* item, QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager)
{
  static bool first = true;
  static VTable<const KwPlaylistItem, int (*)(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager)> vExportToDom;
  if (first)
  {
    vExportToDom.addImplementation(&exportToDom::list);
    first = false;
  }

  if (!vExportToDom(item, document, element, resourceManager))
  {
    KMessageBox::error(0,
        i18n("Unhandled playlist item export to DOM %1").arg(item->typeName()),
        i18n("KWorship"));
  }
}
*/
