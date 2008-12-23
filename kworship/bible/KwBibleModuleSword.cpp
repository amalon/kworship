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
#include "KwBiblePassage.h"

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

bool KwBibleModuleSword::fillPassageVerse(int bookIndex, int chapterIndex, int verseIndex, KwBiblePassage* outPassage)
{
  int bookInTestament = -1;
  int testament = localToTestamentBook(bookIndex, &bookInTestament);
  if (testament >= 0)
  {
    sword::VerseKey verse;
    verse.Headings(0);
    verse.Testament(1+testament);
    verse.Book(1+bookInTestament);
    verse.Chapter(1+chapterIndex);
    verse.Verse(1+verseIndex);

    m_module->setKey(&verse);
    const char* text = m_module->RenderText();
    const char* preverse = m_module->getEntryAttributes()["Heading"]["Preverse"]["0"];
    QString headings;
    if (preverse[0] != '\0')
    {
      headings = QString("<h4>%1</h4>").arg(QString::fromUtf8(preverse));
    }
    outPassage->initVerse(bookIndex, 1+chapterIndex, 1+verseIndex,
                          headings,
                          QString::fromUtf8(text));
    return true;
  }
  return false;
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

