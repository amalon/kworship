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
#include <KwPlaylistSong.h>
#include <KwBiblePlaylistItem.h>
#include <KwPlaylistPresentation.h>
#include <KwCssStyleRule.h>

#include <VTable.h>

#include <KUrl>
#include <KMessageBox>
#include <KLocale>
#include <KSaveFile>

#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QPen>

#include <inttypes.h>

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
                KwPlaylistItem* newItem = 0;
                QString biDiText = item.firstChildElement("BiDiMode").text();
                bool rightToLeft = (biDiText == "bdRightToLeft");
                QString itemType = item.firstChildElement("ItemType").text();
                if (itemType == "siPowerPoint")
                {
                  KwPlaylistPresentation* powerpoint = new KwPlaylistPresentation(QUrl(item.firstChildElement("FilenameRelative").text()));
                  powerpoint->setTitle(item.firstChildElement("Title").text());
                  newItem = powerpoint;
                }
                else if (itemType == "siSong")
                {
                  KwPlaylistText* song = new KwPlaylistText(item.firstChildElement("Title").text(),
                                                            item.firstChildElement("Lyrics").text().split("\n\n"));
                  newItem = song;
                }
                else if (itemType == "siQuickNote")
                {
                  KwPlaylistText* note = new KwPlaylistText(item.firstChildElement("Title").text(),
                                                            readStringList(item.firstChildElement("QuickNote")));
                  newItem = note;
                }
                else if (itemType == "siBible")
                {
                  bool error = true;
                  QStringList verses = readStringList(item.firstChildElement("Verses"));
                  // Try and understand the passage referred to on the first line.
                  static QRegExp rePassage("^(.*)\\s+(\\d+)(:(\\d+)(-(\\d+))?)?\\s+\\(([^\\)]*)\\).*");
                  if (verses.size() >= 1 && rePassage.exactMatch(verses[0]))
                  {
                    error = false;
                    QString bookName = rePassage.cap(1);
                    QString moduleName = rePassage.cap(7);
                    /// @todo Try and get a more accurate set of book ids
                    int bookNum = 0;
                    int chapterNum = rePassage.cap(2).toInt();
                    bool validVerse;
                    int firstVerse = rePassage.cap(4).toInt(&validVerse);
                    if (!validVerse)
                    {
                      firstVerse = 1;
                    }
                    int nextVerse = firstVerse;
                    QStringList verseHeadings;
                    QStringList verseContents;
                    QStringList tempHeadings;
                    for (int i = 1; i < verses.size(); ++i)
                    {
                      const QString& verse = verses[i];
                      // See if it starts with a number, otherwise its a heading
                      static QRegExp reVerseLine("^(\\d+)\\.\\s*(\\S.*)$");
                      if (reVerseLine.exactMatch(verse))
                      {
                        int verseNum = reVerseLine.cap(1).toInt();
                        if (verseNum != nextVerse)
                        {
                          error = true;
                        }
                        nextVerse++;

                        if (!tempHeadings.isEmpty())
                        {
                          verseHeadings += QString("<h4>%1</h4>").arg(tempHeadings.join("<br />\n"));
                        }
                        else
                        {
                          verseHeadings += QString();
                        }
                        verseContents += reVerseLine.cap(2);
                        tempHeadings = QStringList();
                      }
                      else
                      {
                        tempHeadings += verse;
                      }
                    }
                    if (error)
                    {
                      KMessageBox::error(0,
                          i18n("Problems were encountered reading numbered verses in bible passage %1").arg(item.firstChildElement("Title").text()),
                          i18n("KWorship"));
                    }
                    else
                    {
                      KwBiblePlaylistItem* bible = new KwBiblePlaylistItem();
                      KwBiblePassage& passage = bible->passage();
                      passage.setSource(QString(), moduleName, rightToLeft);
                      passage.initBooks(bookNum,1);
                      passage.initBook(bookNum, bookName, chapterNum, 1);
                      passage.initChapter(bookNum, chapterNum, firstVerse, verseContents.size());
                      for (int i = 0; i < verseContents.size(); ++i)
                      {
                        passage.initVerse(bookNum, chapterNum, firstVerse+i, verseHeadings[i], verseContents[i]);
                      }
                      newItem = bible;
                    }
                  }
                  if (error)
                  {
                    KwPlaylistText* bible = new KwPlaylistText(item.firstChildElement("Title").text(),
                                                               verses);
                    newItem = bible;
                  }
                }

                if (0 != newItem)
                {
                  QDomElement overlayStyleEl = playlistNode.firstChildElement("OverlayStyle");
                  if (!overlayStyleEl.isNull())
                  {
                    KwCssStyleSheet* styleRules = new KwCssStyleSheet;
                    KwCssStyleRule overlayStyle;


                    QDomElement fontEl           = overlayStyleEl.firstChildElement("Font");
                    if (!fontEl.isNull())
                    {
                      QFont font;
                      QDomElement fontHeightEl   = fontEl.firstChildElement("Height");
                      if (!fontHeightEl.isNull())
                      {
                        bool ok;
                        int height = fontHeightEl.text().toInt(&ok);
                        if (ok)
                        {
                          font.setPointSize(abs(height));
                        }
                      }
                      QDomElement fontNameEl     = fontEl.firstChildElement("Name");
                      /// @todo Remember font name
                      /// @todo Use font names
                      QDomElement fontStyleEl    = fontEl.firstChildElement("Style");
                      if (!fontStyleEl.isNull())
                      {
                        static QRegExp reFontStyleList("^\\s*\\[(.*)\\]\\s*$");
                        if (reFontStyleList.exactMatch(fontStyleEl.text()))
                        {
                          QStringList styles = reFontStyleList.cap(1).split(",");
                          foreach (QString style, styles)
                          {
                            style = style.trimmed();
                            if (style == "fsBold")
                            {
                              font.setWeight(QFont::Bold);
                            }
                            else if (style == "fsItalic")
                            {
                              font.setStyle(QFont::StyleItalic);
                            }
                          }
                        }
                      }

                      overlayStyle.setStyle<QFont>("text.character.font", font);

                      QDomElement fontColorEl    = fontEl.firstChildElement("Color");
                      if (!fontColorEl.isNull())
                      {
                        bool ok;
                        QColor colour = readColour(fontColorEl, &ok);
                        if (ok)
                        {
                          overlayStyle.setStyle<QBrush>("text.character.brush", QBrush(colour));
                        }
                      }
                    }
                    QDomElement textStyleEl      = overlayStyleEl.firstChildElement("TextStyle");
                    if (!textStyleEl.isNull())
                    {
                      QString style = textStyleEl.text();
                      if (style == "tsShadow")
                      {
                        overlayStyle.setStyle<bool>("text.character.shadow.enabled", true);
                      }
                      else if (style == "tsOutline")
                      {
                        overlayStyle.setStyle<bool>("text.character.outline.enabled", true);
                      }
                    }
                    QDomElement textAlignmentEl  = overlayStyleEl.firstChildElement("TextAlignment");

                    // Shadow
                    QDomElement shadowWidthEl    = overlayStyleEl.firstChildElement("ShadowWidth");
                    if (!shadowWidthEl.isNull())
                    {
                      bool ok;
                      int offset = shadowWidthEl.text().toInt(&ok);
                      if (ok)
                      {
                        overlayStyle.setStyle<int>("text.character.shadow.offset", offset);
                      }
                    }
                    QDomElement shadowColorEl    = overlayStyleEl.firstChildElement("ShadowColor");
                    if (!shadowColorEl.isNull())
                    {
                      bool ok;
                      QColor colour = readColour(shadowColorEl, &ok);
                      if (ok)
                      {
                        overlayStyle.setStyle<QBrush>("text.character.shadow.brush", QBrush(colour));
                      }
                    }

                    // Outline
                    QDomElement outlineWidthEl   = overlayStyleEl.firstChildElement("OutlineWidth");
                    int outlineWidth = 1;
                    if (!outlineWidthEl.isNull())
                    {
                      bool ok;
                      int width = outlineWidthEl.text().toInt(&ok);
                      if (ok)
                      {
                        outlineWidth = width;
                      }
                    }
                    QDomElement outlineColorEl   = overlayStyleEl.firstChildElement("OutlineColor");
                    QColor outlineColour = Qt::black;
                    if (!outlineColorEl.isNull())
                    {
                      bool ok;
                      QColor colour = readColour(outlineColorEl, &ok);
                      if (ok)
                      {
                        outlineColour = colour;
                      }
                    }
                    overlayStyle.setStyle<QPen>("text.character.outline.pen", QPen(outlineColour, outlineWidth));

                    QDomElement fillColorEl      = overlayStyleEl.firstChildElement("FillColor");
                    if (!fillColorEl.isNull())
                    {
                      bool ok;
                      QColor colour = readColour(fillColorEl, &ok);
                      if (ok)
                      {
                        overlayStyle.setStyle<QBrush>("background.brush", QBrush(colour));
                      }
                    }
                    QDomElement imageFilenameEl  = overlayStyleEl.firstChildElement("ImageFilename");
                    //overlayStyle.setStyle<KwResourceLink>("background.image.src", KUrl("file:///home/james/media/images/projector/misc/bible.jpg"));
                    QDomElement imageAlignmentEl = overlayStyleEl.firstChildElement("ImageAlignment");

                    // Margins
                    QDomElement marginRightEl    = overlayStyleEl.firstChildElement("MarginRight");
                    if (!marginRightEl.isNull())
                    {
                      bool ok;
                      float margin = marginRightEl.text().toFloat(&ok);
                      if (ok)
                      {
                        overlayStyle.setStyle<float>("text.layout.margins.right", margin);
                      }
                    }
                    QDomElement marginLeftEl     = overlayStyleEl.firstChildElement("MarginLeft");
                    if (!marginLeftEl.isNull())
                    {
                      bool ok;
                      float margin = marginLeftEl.text().toFloat(&ok);
                      if (ok)
                      {
                        overlayStyle.setStyle<float>("text.layout.margins.left", margin);
                      }
                    }
                    QDomElement marginTopEl      = overlayStyleEl.firstChildElement("MarginTop");
                    if (!marginTopEl.isNull())
                    {
                      bool ok;
                      float margin = marginTopEl.text().toFloat(&ok);
                      if (ok)
                      {
                        overlayStyle.setStyle<float>("text.layout.margins.top", margin);
                      }
                    }
                    QDomElement marginBottomEl   = overlayStyleEl.firstChildElement("MarginBottom");
                    if (!marginBottomEl.isNull())
                    {
                      bool ok;
                      float margin = marginBottomEl.text().toFloat(&ok);
                      if (ok)
                      {
                        overlayStyle.setStyle<float>("text.layout.margins.bottom", margin);
                      }
                    }

                    styleRules->addRule(overlayStyle);
                    newItem->addStyleSheet(styleRules);
                  }

                  list->addItem(newItem);
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

/// Contains implementations of export functions.
class KwZionworxFilter::ExportToDom
{
  public:

    static QDomElement createPlaylistNode(QDomDocument& document, QDomElement& element)
    {
      QDomElement node = document.createElement("TPlayListNode");
      element.appendChild(node);
      return node;
    }
    static QDomElement createOverlayStyle(QDomDocument& document, QDomElement& element)
    {
      QDomElement style = document.createElement("OverlayStyle");
      element.appendChild(style);
      return style;
    }
    static QDomElement createPlaylistItem(QDomDocument& document, QDomElement& element,
                                          const QString& type, const QString& title, bool rightToLeft)
    {
      QDomElement item = document.createElement("PlayListItem");
      {
        QDomElement typeEl = document.createElement("ItemType");
        typeEl.appendChild(document.createTextNode(type));
        item.appendChild(typeEl);
      }
      {
        QDomElement titleEl = document.createElement("Title");
        titleEl.appendChild(document.createTextNode(title));
        item.appendChild(titleEl);
      }
      {
        QDomElement biDiEl = document.createElement("BiDiMode");
        biDiEl.appendChild(document.createTextNode(rightToLeft ? "bdRightToLeft" : "bdLeftToRight"));
        item.appendChild(biDiEl);
      }
      element.appendChild(item);
      return item;
    }
    static int list(const KwPlaylistList* self, QDomDocument& document, QDomElement& element)
    {
      for (int i = 0; i < self->getItemCount(); ++i)
      {
        call(self->getItem(i), document, element);
      }
      return 0;
    }
    static int song(const KwPlaylistSong* self, QDomDocument& document, QDomElement& element)
    {
      QDomElement node = createPlaylistNode(document, element);
      return 0;
    }
    static int note(const KwPlaylistText* self, QDomDocument& document, QDomElement& element)
    {
      QDomElement node = createPlaylistNode(document, element);
      return 0;
    }
    static int bible(const KwBiblePlaylistItem* self, QDomDocument& document, QDomElement& element)
    {
      QDomElement node = createPlaylistNode(document, element);
      QDomElement style = createOverlayStyle(document, node);
      const KwBiblePassage& passage = self->passage();
      QDomElement item = createPlaylistItem(document, node,
                                            "siBible", passage.textualKey(),
                                            passage.isRightToLeft());

      QDomElement versesEl = document.createElement("Verses");
      versesEl.appendChild(document.createTextNode("(TTntStringList)"));
      {
        QDomElement definedPropsEl = document.createElement("DefinedProperties");
        QByteArray propsData;
        KwPascalStream data(&propsData, QIODevice::WriteOnly);

        QStringList verses;
        verses << passage.textualKey();
        for (int book = passage.firstBookNumber(); book <= passage.lastBookNumber(); ++book)
        {
          for (int chap = passage.firstChapterNumber(book); chap <= passage.lastChapterNumber(book); ++chap)
          {
            for (int verse = passage.firstVerseNumber(book, chap); verse <= passage.lastVerseNumber(book, chap); ++verse)
            {
              const QString& headings = passage.verseHeadings(book, chap, verse, true);
              if (!headings.isEmpty())
              {
                verses += headings;
              }
              const QString& content = passage.verseContent(book, chap, verse, true);
              if (!content.isEmpty())
              {
                verses += i18nc("Verse number, bible verse, for zionworx export", "%1.  %2").arg(verse).arg(content);
              }
            }
          }
        }
        data.writeProperty("Strings", verses);

        propsData = propsData.toBase64();
        definedPropsEl.appendChild(document.createTextNode(propsData));
        versesEl.appendChild(definedPropsEl);
      }
      item.appendChild(versesEl);
      return 0;
    }
    static int presentation(const KwPlaylistPresentation* self, QDomDocument& document, QDomElement& element)
    {
      QDomElement node = createPlaylistNode(document, element);
      QDomElement item = createPlaylistItem(document, node,
                                            "siPowerPoint", self->title(),
                                            false);

      return 0;
    }

    static void init()
    {
      static bool done = false;
      if (!done)
      {
        call.addImplementation(&list);
        call.addImplementation(&song);
        call.addImplementation(&note);
        call.addImplementation(&bible);
        call.addImplementation(&presentation);
        done = true;
      }
    }

    typedef VTable<const KwPlaylistItem, int (*)(QDomDocument& document, QDomElement& element)> ExportVTable;
    static ExportVTable call;
};
KwZionworxFilter::ExportToDom::ExportVTable KwZionworxFilter::ExportToDom::call;

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

  // Create document
  QDomDocument domDoc;
  QDomElement root = domDoc.createElement("Root");
  domDoc.appendChild(root);

  // Version element
  QDomElement version = domDoc.createElement("ZionWorx");
  version.setAttribute("Version", 2.6);
  version.setAttribute("FullFilename", url.toLocalFile());
  root.appendChild(version);

  // Playlist nodes element
  QDomElement playlist = domDoc.createElement("PlayListNodes");
  ExportToDom::init();
  ExportToDom::call(doc->playlist(), domDoc, playlist);
  root.appendChild(playlist);

  // Write document to file
  QByteArray xml = domDoc.toByteArray(2);
  file.write(xml, xml.size());

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

/// Read a colour from DOM.
QColor KwZionworxFilter::readColour(const QDomElement& el, bool* ok) const
{
  bool isOk = false;

  static QHash<QString, QColor> colours;
  static bool inited = false;
  if (!inited)
  {
    colours["clWhite"]       = Qt::white;
    colours["clBlack"]       = Qt::black;
    colours["clRed"]         = Qt::red;
    colours["clDarkRed"]     = Qt::darkRed;
    colours["clGreen"]       = Qt::green;
    colours["clDarkGreen"]   = Qt::darkGreen;
    colours["clBlue"]        = Qt::blue;
    colours["clDarkBlue"]    = Qt::darkBlue;
    colours["clCyan"]        = Qt::cyan;
    colours["clDarkCyan"]    = Qt::darkCyan;
    colours["clMagenta"]     = Qt::magenta;
    colours["clDarkMagenta"] = Qt::darkMagenta;
    colours["clYellow"]      = Qt::yellow;
    colours["clDarkGray"]    = Qt::darkYellow;
    colours["clGray"]        = Qt::gray;
    colours["clDarkGray"]    = Qt::darkGray;
    colours["clLightGray"]   = Qt::lightGray;
    inited = true;
  }

  QString colourName = el.text();
  QColor result;
  uint32_t colourNum = colourName.toInt(&isOk);
  if (isOk)
  {
    // 0xff in msb apparently changes byte order
    if ((colourNum >> 24) & 0xFF == 0xFF)
    {
      // least significant byte is blue, followed by green and red
      result.setRgb((colourNum >> 16) & 0xFF,
                    (colourNum >> 8)  & 0xFF,
                     colourNum        & 0xFF);
    }
    else
    {
      // least significant byte is red, followed by green and blue
      result.setRgb( colourNum        & 0xFF,
                    (colourNum >> 8)  & 0xFF,
                    (colourNum >> 16) & 0xFF);
    }
  }
  else if (colours.contains(colourName))
  {
    result = colours[colourName];
    isOk = true;
  }

  if (0 != ok)
  {
    *ok = isOk;
  }
  return result;
}
