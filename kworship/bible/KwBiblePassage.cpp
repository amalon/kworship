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
 * @file KwBiblePassage.cpp
 * @brief A passage of rendered bible text.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBiblePassage.h"

#include <KLocale>

/*
 * Constructors + destructor
 */

/// Default constructor.
KwBiblePassage::KwBiblePassage()
: m_managerId()
, m_moduleId()
, m_key()
, m_firstBook(0)
, m_numBooks(0)
, m_books(0)
{
}

/// Destructor.
KwBiblePassage::~KwBiblePassage()
{
  // Deep cleanup operation
  for (int bookIndex = 0; bookIndex < m_numBooks; ++bookIndex)
  {
    Book* book = &m_books[bookIndex];
    for (int chapterIndex = 0; chapterIndex < book->numChapters; ++chapterIndex)
    {
      Chapter* chapter = &book->chapters[chapterIndex];
      delete chapter->verses;
    }
    delete book->chapters;
  }
  delete m_books;
}

/*
 * Main interface
 */

/// Clear the passage.
void KwBiblePassage::clear()
{
}

/// Set the source module.
void KwBiblePassage::setSource(const QString& managerId, const QString& moduleId)
{
}

/// Initialise the books in the passage.
void KwBiblePassage::initBooks(int firstBook, int numBooks)
{
}

/// Initialise a book in the passage.
void KwBiblePassage::initBook(int bookNumber,
                              const QString& name, int firstChapter, int numChapters)
{
}

/// Initialise a chapter in the passage.
void KwBiblePassage::initChapter(int bookNumber, int chapterNumber,
                                 int firstVerse, int numVerses)
{
}

/// Initialise a verse in the passage.
void KwBiblePassage::initVerse(int bookNumber, int chapterNumber, int verseNumber,
                               const QString& headings, const QString& content)
{
}

/*
 * Accessors
 */

/// Find whether the passage is empty.
bool KwBiblePassage::isEmpty() const
{
}

/// Get textual key of this passage.
QString KwBiblePassage::textualKey() const
{
  // Empty range
  if (0 == m_numBooks)
  {
    return i18nc("empty bible passage", "empty");
  }
  Q_ASSERT(m_books[0].numChapters > 0);
  Q_ASSERT(m_books[0].chapters[0].numVerses > 0);

  QString result = i18nc("bible index (book, chapter:verse)", "%1 %2",
                         m_books[0].name,
                         i18nc("bible index (chapter:verse)", "%1:%2",
                               m_books[0].firstChapter,
                               m_books[0].chapters[0].firstVerse));
  Book* lastBook = &m_books[m_numBooks - 1];
  Chapter* lastChapter = &lastBook->chapters[lastBook->numChapters - 1];
  // Overlapping multiple books
  if (m_numBooks > 1)
  {
    result = i18nc("bible passage range (book chapter:verse, book chapter:verse)", "%1 - %2", result,
                   i18nc("bible index (book, chapter:verse)", "%1 %2",
                         lastBook->name,
                         i18nc("bible index (chapter:verse)", "%1:%2",
                               lastBook->firstChapter  + lastBook->numChapters  - 1,
                               lastChapter->firstVerse + lastChapter->numVerses - 1)));
  }
  // Overlapping multiple chapters
  else if (lastBook->numChapters > 1)
  {
    result = i18nc("bible passage range (book chapter:verse, chapter:verse)", "%1 - %2", result,
                   i18nc("bible index (chapter:verse)", "%1:%2",
                        lastBook->firstChapter  + lastBook->numChapters  - 1,
                        lastChapter->firstVerse + lastChapter->numVerses - 1));
  }
  // Overlapping multiple verses 
  else if (lastChapter->numVerses > 1)
  {
    result = i18nc("bible passage range (book chapter:verse, verse)", "%1-%2", result,
                   lastChapter->firstVerse + lastChapter->numVerses - 1);
  }

  // Module name is quite important too
  return i18nc("bible index (range, version)", "%1 (%2)", result, m_moduleId);
}

/// Get the first book number in the passage.
int KwBiblePassage::firstBookNumber() const
{
}

/// Get the last book number in the passage.
int KwBiblePassage::lastBookNumber() const
{
}

/// Get the first chapter number in a book of the passage.
int KwBiblePassage::firstChapterNumber(int bookNumber) const
{
}

/// Get the last chapter number in a book of the passage.
int KwBiblePassage::lastChapterNumber(int bookNumber) const
{
}

/// Get the first verse number in a chapter of the passage.
int KwBiblePassage::firstVerseNumber(int bookNumber, int chapterNumber) const
{
}

/// Get the last verse number in a chapter of the passage.
int KwBiblePassage::lastVerseNumber(int bookNumber, int chapterNumber) const
{
}
