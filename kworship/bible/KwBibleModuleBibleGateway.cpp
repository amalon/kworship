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
 * @file KwBibleModuleBibleGateway.cpp
 * @brief A BibleGateway bible module.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBibleModuleBibleGateway.h"
#include "KwBiblePassage.h"

#include <KIO/NetAccess>
#include <KMessageBox>
#include <KLocale>
#include <dom/html_document.h>
#include <dom/html_element.h>
#include <dom/html_block.h>

#include <QStringList>
#include <QFile>

/*
 * Constructors + destructor
 */

/// Default constructor.
KwBibleModuleBibleGateway::KwBibleModuleBibleGateway(int id)
: KwBibleModule()
{
  KUrl url(QString("http://www.biblegateway.com/versions/index.php?action=getVersionInfo&vid=%1").arg(id));

  QString tmpFile;
  if (KIO::NetAccess::download(url, tmpFile, 0))
  {
    QFile file(tmpFile);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
      QByteArray rawPage = file.readAll();
      file.close();

      DOM::HTMLDocument doc;
      doc.loadXML(QString::fromUtf8(rawPage));
      DOM::Element bookList = doc.getElementById("booklist");
      bool tableFound = false;
      if (!bookList.isNull())
      {
        // Get the next table
        DOM::Node sibling = bookList.nextSibling();
        while (!sibling.isNull() && sibling.nodeType() != DOM::Node::ELEMENT_NODE)
        {
          sibling = sibling.nextSibling();
        }
        DOM::Element tableElement(sibling);
        if (!tableElement.isNull() && tableElement.tagName() == "table")
        {
          tableFound = true;
          // Each row except header is a book
          DOM::NodeList rows = tableElement.getElementsByTagName("tr");
          bool firstRow = true;
          for (unsigned int row = 0; row < rows.length(); ++row)
          {
            DOM::NodeList cells = DOM::Element(rows.item(row)).getElementsByTagName("td");
            if (cells.length() == 2)
            {
              // First cell is the name
              m_bookList.push_back(Book());
              Book* book = &m_bookList[m_bookList.size()-1];
              book->name = DOM::HTMLElement(cells.item(0)).innerText().string();
              // Also check if text is right-to-left
              if (firstRow)
              {
                setRightToLeft(DOM::HTMLElement(cells.item(0)).className().string().toLower().contains("rtl"));
                firstRow = false;
              }
              // Second cell is the chapter links
              DOM::NodeList chapterLinks = DOM::Element(cells.item(1)).getElementsByTagName("a");
              for (unsigned int chapter = 0; chapter < chapterLinks.length(); ++chapter)
              {
                // Check the chapter number is right
                DOM::HTMLElement link = chapterLinks.item(chapter);
                bool numeric;
                int check = link.innerText().string().toInt(&numeric);
                if (!numeric || check != (int)chapter+1)
                {
                  KMessageBox::error(0, i18n("Error parsing webpage: %1", i18n("Non sequential chapter list in book '%1'", book->name)));
                  break;
                }
                // Get the link
                book->chapters.push_back(Chapter());
                Chapter* chapter = &book->chapters[book->chapters.size()-1];
                chapter->url = "http://www.biblegateway.com" + link.getAttribute("href").string();
                chapter->fetched = false;
              }
            }
          }
        }
      }
      if (!tableFound)
      {
        // Book list reference node not found
        KMessageBox::error(0, i18n("Error parsing webpage: %1", i18n("Book list table not found")));
      }
    }

    KIO::NetAccess::removeTempFile(tmpFile);
  }
  else
  {
    KMessageBox::error(0, KIO::NetAccess::lastErrorString());
  }
}

/// Destructor.
KwBibleModuleBibleGateway::~KwBibleModuleBibleGateway()
{
}

/*
 * Main interface
 */

QString KwBibleModuleBibleGateway::name()
{
  return QString();
}

QString KwBibleModuleBibleGateway::description()
{
  return QString();
}

int KwBibleModuleBibleGateway::numChapters(int book)
{
  if (book >= 0 && book < m_bookList.size())
  {
    return m_bookList[book].chapters.size();
  }
  return 0;
}

int KwBibleModuleBibleGateway::numVerses(int book, int chapter)
{
  Chapter* chap = fetchChapter(book, chapter);
  if (0 != chap)
  {
    return chap->verses.size();
  }
  else
  {
    return 0;
  }
}

bool KwBibleModuleBibleGateway::fillPassageVerse(int bookIndex, int chapterIndex, int verseIndex, KwBiblePassage* outPassage)
{
  Chapter* chapter = fetchChapter(bookIndex, chapterIndex);
  if (0 != chapter)
  {
    outPassage->initVerse(bookIndex, 1+chapterIndex, 1+verseIndex,
                          chapter->verses[verseIndex].heading,
                          chapter->verses[verseIndex].content);
  }
  return false;
}

/*
 * Protected virtual interface
 */

void KwBibleModuleBibleGateway::obtainBooks()
{
  QStringList list;
  for (int book = 0; book < m_bookList.size(); ++book)
  {
    list << m_bookList[book].name;
  }
  setBooks(list);
}

/*
 * Private functions
 */

/// Ensure chapter contents are fetched.
KwBibleModuleBibleGateway::Chapter* KwBibleModuleBibleGateway::fetchChapter(int book, int chapter)
{
  if (book >= 0 && book < m_bookList.size())
  {
    Book* bookObj = &m_bookList[book];
    if (chapter >= 0 && chapter < m_bookList[book].chapters.size())
    {
      Chapter* chap = &bookObj->chapters[chapter];
      if (!chap->fetched)
      {
        QString tmpFile;
        if (KIO::NetAccess::download(chap->url, tmpFile, 0))
        {
          QFile file(tmpFile);
          if (file.open(QFile::ReadOnly | QFile::Text))
          {
            QByteArray rawPage = file.readAll();
            file.close();

            DOM::HTMLDocument doc;
            doc.loadXML(QString::fromUtf8(rawPage));

            // Find all spans with class="sup"
            DOM::NodeList sups = doc.body().getElementsByClassName("sup");
            int verse = 0;
            for (unsigned int i = 0; i < sups.length(); ++i)
            {
              DOM::HTMLElement span = sups.item(i);
              if (span.tagName() == "span")
              {
                // Get the verse number and validate
                bool numeric;
                QString verseNumber = span.innerText().string();
                Verse verseInfo;
                int check = verseNumber.toInt(&numeric);
                if (!numeric)
                {
                  // Its not going to be a verse if it isn't numeric
                  KMessageBox::error(0, i18n("Error parsing webpage: %1", i18n("Non numeric superscript encountered: '%1'. It may correspond to a verse range.", verseNumber)));
                  continue;
                }
                ++verse;
                if (check != verse)
                {
                  KMessageBox::error(0, i18n("Error parsing webpage: %1", i18n("Non sequential verse list in chapter %1 of book '%2'. Expected verse %3 but got verse %4.", (chapter+1), bookObj->name, verse, check)));
                  break;
                }

                // Get any headers before it
                DOM::Node sibling;
                sibling = span.previousSibling();
                while (!sibling.isNull())
                {
                  DOM::Element siblingElement = sibling;
                  if (!siblingElement.isNull())
                  {
                    // Stop at a span class="sup"
                    if (siblingElement.tagName() == "span" && siblingElement.getAttribute("class") == "sup")
                    {
                      break;
                    }
                    // See if its an interesting heading
                    DOM::HTMLHeadingElement heading = siblingElement;
                    if (!heading.isNull())
                    {
                      verseInfo.heading = heading.toHTML() + verseInfo.heading;
                    }
                  }
                  sibling = sibling.previousSibling();
                }

                // Get any text after it until the next span
                sibling = span.nextSibling();
                while (!sibling.isNull())
                {
                  DOM::Element siblingElement = sibling;
                  if (!siblingElement.isNull())
                  {
                    // Stop at a span class="sup"
                    if (siblingElement.tagName() == "span" && siblingElement.getAttribute("class") == "sup")
                    {
                      break;
                    }
                    // Also stop at headings
                    DOM::HTMLHeadingElement heading = siblingElement;
                    if (!heading.isNull())
                    {
                      break;
                    }
                  }
                  verseInfo.content += sibling.toHTML();
                  sibling = sibling.nextSibling();
                }

                chap->verses.push_back(verseInfo);
              }
            }
          }

          KIO::NetAccess::removeTempFile(tmpFile);
        }
        else
        {
          KMessageBox::error(0, KIO::NetAccess::lastErrorString());
        }
        chap->fetched = true;
      }

      return chap;
    }
  }
  return 0;
}

