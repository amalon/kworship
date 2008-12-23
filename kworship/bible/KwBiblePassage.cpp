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
}

/*
 * Main interface
 */

/// Clear the passage.
void KwBiblePassage::clearBooks()
{
  // Deep cleanup operation
  if (0 != m_books)
  {
    int lastBook = m_firstBook + m_numBooks;
    for (int bookNumber = m_firstBook; bookNumber < lastBook; ++bookNumber)
    {
      clearChapters(bookNumber);
    }
    delete [] m_books;
    m_books = 0;
  }
}

/// Clear the chapters in a book.
void KwBiblePassage::clearChapters(int bookNumber)
{
  Q_ASSERT(0 != m_books && bookNumber >= m_firstBook && bookNumber < m_firstBook+m_numBooks);
  Book* book = &m_books[bookNumber-m_firstBook];
  if (0 != book->chapters)
  {
    int maxChapter = book->firstChapter + book->numChapters;
    for (int chapterNumber = book->firstChapter; chapterNumber < maxChapter; ++chapterNumber)
    {
      clearVerses(bookNumber, chapterNumber);
    }
    delete [] book->chapters;
    book->chapters = 0;
  }
}

/// Clear the verses in a chapter.
void KwBiblePassage::clearVerses(int bookNumber, int chapterNumber)
{
  bookNumber -= m_firstBook;
  Q_ASSERT(0 != m_books && bookNumber >= 0 && bookNumber < m_numBooks);
  chapterNumber -= m_books[bookNumber].firstChapter;
  Q_ASSERT(0 != m_books[bookNumber].chapters && chapterNumber >= 0 && chapterNumber < m_books[bookNumber].numChapters);
  Chapter* chapter = &m_books[bookNumber].chapters[chapterNumber];
  if (0 != chapter->verses)
  {
    delete [] chapter->verses;
    chapter->verses = 0;
  }
}

/// Set the source module.
void KwBiblePassage::setSource(const QString& managerId, const QString& moduleId)
{
  m_managerId = managerId;
  m_moduleId = moduleId;
}

/// Initialise the books in the passage.
void KwBiblePassage::initBooks(int firstBook, int numBooks)
{
  clearBooks();
  m_firstBook = firstBook;
  m_numBooks = numBooks;
  m_books = new Book[numBooks];
  for (int i = 0; i < numBooks; ++i)
  {
    m_books[i].firstChapter = -1;
    m_books[i].numChapters = 0;
    m_books[i].chapters = 0;
  }
}

/// Initialise a book in the passage.
void KwBiblePassage::initBook(int bookNumber,
                              const QString& name, int firstChapter, int numChapters)
{
  clearChapters(bookNumber);
  bookNumber -= m_firstBook;
  Book* book = &m_books[bookNumber];
  book->name = name;
  book->firstChapter = firstChapter;
  book->numChapters = numChapters;
  book->chapters = new Chapter[numChapters];
  for (int i = 0; i < numChapters; ++i)
  {
    book->chapters[i].firstVerse = -1;
    book->chapters[i].numVerses = 0;
    book->chapters[i].verses = 0;
  }
}

/// Initialise a chapter in the passage.
void KwBiblePassage::initChapter(int bookNumber, int chapterNumber,
                                 int firstVerse, int numVerses)
{
  clearVerses(bookNumber, chapterNumber);
  bookNumber -= m_firstBook;
  chapterNumber -= m_books[bookNumber].firstChapter;
  Chapter* chapter = &m_books[bookNumber].chapters[chapterNumber];
  chapter->firstVerse = firstVerse;
  chapter->numVerses = numVerses;
  chapter->verses = new Verse[numVerses];
}

/// Initialise a verse in the passage.
void KwBiblePassage::initVerse(int bookNumber, int chapterNumber, int verseNumber,
                               const QString& headings, const QString& content)
{
  bookNumber -= m_firstBook;
  Q_ASSERT(0 != m_books && bookNumber >= 0 && bookNumber < m_numBooks);
  chapterNumber -= m_books[bookNumber].firstChapter;
  Q_ASSERT(0 != m_books[bookNumber].chapters && chapterNumber >= 0 && chapterNumber < m_books[bookNumber].numChapters);
  verseNumber -= m_books[bookNumber].chapters[chapterNumber].firstVerse;
  Q_ASSERT(0 != m_books[bookNumber].chapters[chapterNumber].verses && verseNumber >= 0 && verseNumber < m_books[bookNumber].chapters[chapterNumber].numVerses);

  Verse* verse = &m_books[bookNumber].chapters[chapterNumber].verses[verseNumber];
  verse->headings = headings;
  verse->content = content;
}

/*
 * Accessors
 */

/// Find whether the passage is empty.
bool KwBiblePassage::isEmpty() const
{
  return (m_books == 0);
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

  /**
   * @bug 2008-dec-22: There is a bug in Qt's handling of right-to-left scripts somewhere
   *                   in QString::arg(QString) - in this case from m_books[i].name.
   *                   It results in the substitutions taking place in the wrong order.
   *                   There also appear to be similar problems rendering even if the
   *                   substitutions appear to take place correctly.
   *                   I haven't managed to find a satisfactory work-around for this problem
   *                   so I'm ignoring it for the time being.
   */

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
  Q_ASSERT(false && "Unimplemented");
}

/// Get the last book number in the passage.
int KwBiblePassage::lastBookNumber() const
{
  Q_ASSERT(false && "Unimplemented");
}

/// Get the first chapter number in a book of the passage.
int KwBiblePassage::firstChapterNumber(int bookNumber) const
{
  Q_ASSERT(false && "Unimplemented");
}

/// Get the last chapter number in a book of the passage.
int KwBiblePassage::lastChapterNumber(int bookNumber) const
{
  Q_ASSERT(false && "Unimplemented");
}

/// Get the first verse number in a chapter of the passage.
int KwBiblePassage::firstVerseNumber(int bookNumber, int chapterNumber) const
{
  Q_ASSERT(false && "Unimplemented");
}

/// Get the last verse number in a chapter of the passage.
int KwBiblePassage::lastVerseNumber(int bookNumber, int chapterNumber) const
{
  Q_ASSERT(false && "Unimplemented");
}

/*
 * Text extraction
 */

/// Get the entire passaage rendered as HTML.
QString KwBiblePassage::renderedText()
{
  QString result;
  Book* book = m_books;
  for (int bookIndex = 0; bookIndex < m_numBooks; ++bookIndex)
  {
    Chapter* chapter = book->chapters;
    for (int chapterIndex = 0; chapterIndex < book->numChapters; ++chapterIndex)
    {
      Verse* verse = chapter->verses;
      for (int verseIndex = 0; verseIndex < chapter->numVerses; ++verseIndex)
      {
        if (!verse->headings.isEmpty())
        {
          result += verse->headings;
        }
        if (!verse->content.isEmpty())
        {
          result += QString("<sup>%1</sup>").arg(chapter->firstVerse + verseIndex);
          result += verse->content;
        }
        ++verse;
      }
      ++chapter;
    }
    ++book;
  }
  return result;
}
