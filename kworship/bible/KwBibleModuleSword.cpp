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
 * @file KwBibleModuleSword.cpp
 * @brief A SWORD bible module.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBibleModuleSword.h"

#include <QStringList>

#include <swmodule.h>
#include <swtext.h>
#include <versekey.h>

/*
 * Constructors + destructor
 */

/// Default constructor.
KwBibleModuleSword::KwBibleModuleSword(sword::SWText* module)
: KwBibleModule()
, m_module(module)
{
  // Get the range of books.
  bool oldSCL = module->getSkipConsecutiveLinks();
  module->setSkipConsecutiveLinks(true);

  {
    module->setPosition(sword::TOP);
    sword::VerseKey key = module->KeyText();
    m_firstBibleBookIndex = testamentBookToBible(key.Testament()-1, key.Book()-1);
  }

  {
    module->setPosition(sword::BOTTOM);
    sword::VerseKey key = module->KeyText();
    m_lastBibleBookIndex = testamentBookToBible(key.Testament()-1, key.Book()-1);
  }

  module->setSkipConsecutiveLinks(oldSCL);
}

/// Destructor.
KwBibleModuleSword::~KwBibleModuleSword()
{
}

/*
 * Main interface
 */

QString KwBibleModuleSword::name()
{
  return m_module->Name();
}

QString KwBibleModuleSword::description()
{
  return m_module->Description();
}

int KwBibleModuleSword::numChapters(int book)
{
  int testamentBook;
  int testament = localToTestamentBook(book, &testamentBook);
  if (testament >= 0)
  {
    sword::VerseKey key = m_module->getKey();
    return key.books[testament][testamentBook].chapmax;
  }
  return 0;
}

int KwBibleModuleSword::numVerses(int book, int chapter)
{
  if (book >= 0 && chapter >= 0)
  {
    int testamentBook;
    int testament = localToTestamentBook(book, &testamentBook);
    if (testament >= 0)
    {
      sword::VerseKey key = m_module->getKey();
      if (chapter < key.books[testament][testamentBook].chapmax)
      {
        return key.books[testament][testamentBook].versemax[chapter];
      }
    }
  }
  return 0;
}

bool KwBibleModuleSword::fillPassage(const Key& key, KwBiblePassage* outPassage) const
{
  return false;
}

QString KwBibleModuleSword::renderText(const KwBibleModule::Key& key)
{
  QString result;
  int startBook, endBook;
  int startTestament = localToTestamentBook(key.start.book, &startBook);
  int endTestament   = localToTestamentBook(key.end.book,   &endBook);
  if (startTestament >= 0)
  {
    if (endTestament == -1)
    {
      endTestament = startTestament;
      endBook = startBook;
    }
    int startChapter = key.start.chapter;
    int endChapter = key.end.chapter;
    if (startChapter < 0)
    {
      startChapter = 0;
      endChapter = numChapters(testamentBookToLocal(endTestament, endBook))-1;
    }
    else if (endChapter < 0)
    {
      endChapter = startChapter;
    }

    int startVerse = key.start.verse;
    int endVerse = key.end.verse;
    if (startVerse < 0)
    {
      startVerse = 0;
      endVerse = numVerses(testamentBookToLocal(endTestament, endBook), endChapter)-1;
    }
    else if (endVerse < 0)
    {
      endVerse = startVerse;
    }

    sword::VerseKey vkey;
    vkey.LowerBound().Testament(1+startTestament);
    vkey.LowerBound().Book(1+startBook);
    vkey.LowerBound().Chapter(1+startChapter);
    vkey.LowerBound().Verse(1+startVerse);
    vkey.UpperBound().Testament(1+endTestament);
    vkey.UpperBound().Book(1+endBook);
    vkey.UpperBound().Chapter(1+endChapter);
    vkey.UpperBound().Verse(1+endVerse);
    //std::cout << startTestament << " " << startBook << " " << startChapter << ":" << startVerse << std::endl;
    //std::cout << endTestament << " " << endBook << " " << endChapter << ":" << endVerse << std::endl;

    sword::VerseKey verse = vkey.LowerBound();
    verse.Headings(1);
    sword::VerseKey last = vkey.UpperBound();
    Q_ASSERT(verse.isTraversable());

    // verse must be before last
    if (verse.compare(last) <= 0)
    {
      int limit = 500;
      while (--limit > 0)
      {
        m_module->setKey(&verse);
        const char* text = m_module->RenderText();
        const char* preverse = m_module->getEntryAttributes()["Heading"]["Preverse"]["0"];
        result += " ";
        if (preverse[0] != '\0')
        {
          result += QString("<h1>%1</h1>").arg(QString::fromUtf8(preverse));
        }
        if (QLatin1String(text) != QLatin1String(""))
        {
          result += QString("<sup>%1</sup>").arg(verse.Verse()) + QString::fromUtf8(text);
        }
        if (verse.equals(last))
        {
          break;
        }
        verse.increment(1);
      }
    }
  }

  return result;
}

/*
 * Protected virtual interface
 */

void KwBibleModuleSword::obtainBooks()
{
  // List books
  QStringList books; 
  sword::VerseKey key = m_module->getKey();
  for (int bibleIndex = m_firstBibleBookIndex; bibleIndex <= m_lastBibleBookIndex; ++bibleIndex)
  {
    int testamentBook;
    int testament = bibleToTestamentBook(bibleIndex, &testamentBook);
    Q_ASSERT(testament >= 0);
    books << QString::fromUtf8(key.books[testament][testamentBook].name);
  }
  setBooks(books);
}

/*
 * Internal functions
 */

/// Convert a local book index to a bible book index.
int KwBibleModuleSword::localToBible(int localIndex) const
{
  int result = -1;
  if (localIndex >= 0 && m_firstBibleBookIndex + localIndex <= m_lastBibleBookIndex)
  {
    result = m_firstBibleBookIndex + localIndex;
  }
  return result;
}

/// Convert a bible book index to a local book index.
int KwBibleModuleSword::bibleToLocal(int bibleIndex) const
{
  int result = -1;
  if (bibleIndex >= m_firstBibleBookIndex && bibleIndex <= m_lastBibleBookIndex)
  {
    result = bibleIndex - m_firstBibleBookIndex;
  }
  return result;
}

/// Convert a testament & book number to a bible book index.
int KwBibleModuleSword::testamentBookToBible(int testament, int book) const
{
  if (testament >= 0 && book >= 0)
  {
    sword::VerseKey key = m_module->getKey();
    if (book < key.BMAX[testament])
    {
      if (testament == 0)
      {
        return book;
      }
      else if (testament == 1)
      {
        return key.BMAX[0] + book;
      }
    }
  }
  return -1;
}

/// Convert a bible book index into a testament and book number.
int KwBibleModuleSword::bibleToTestamentBook(int bibleIndex, int* book) const
{
  if (bibleIndex >= 0)
  {
    sword::VerseKey key = m_module->getKey();
    // Old testament?
    if (bibleIndex < key.BMAX[0])
    {
      *book = bibleIndex;
      return 0;
    }
    // New testament?
    else if (bibleIndex < key.BMAX[0] + key.BMAX[1])
    {
      *book = bibleIndex - key.BMAX[0];
      return 1;
    }
  }
  return -1;
}

/// Convert a testament & book number to a local book index.
int KwBibleModuleSword::testamentBookToLocal(int testament, int book) const
{
  return bibleToLocal(testamentBookToBible(testament, book));
}

/// Convert a local book index into a testament and book number.
int KwBibleModuleSword::localToTestamentBook(int localIndex, int* book) const
{
  return bibleToTestamentBook(localToBible(localIndex), book);
}

