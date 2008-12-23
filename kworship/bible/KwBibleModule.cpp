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
 * @file KwBibleModule.cpp
 * @brief An abstract bible module (analagous to a SWORD module).
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBibleModule.h"
#include "KwBiblePassage.h"

#include <QRegExp>

/*
 * Constructors + destructor
 */

/// Default constructor.
KwBibleModule::KwBibleModule()
: m_books()
, m_rightToLeft(false)
{
}

/// Destructor.
KwBibleModule::~KwBibleModule()
{
}

/*
 * Main interface
 */

/// Create a key from a string.
KwBibleModule::Key KwBibleModule::createKey(const QString& text, bool* valid)
{
  // Find the key relative to the first chapter of the first book.
  return createKey(createKey(0, 0), text);
}

/// Create a key from a string relative to another key.
KwBibleModule::Key KwBibleModule::createKey(const Key& other, const QString& text, bool* valid)
{
  Key key = other;
  static QRegExp re("^\\s*"                       // Must from beginning (ignore whitespace)
                    // 1( 2( 3() 4() ) )
                    "(((\\S+)|\"([^\"]+)\")\\s+)?" // Optional book name followed by spaces
                    // 5( 6() )
                    "((\\d+)[:.])?"               // Optional chapter number followed by [:.]
                    // 7()
                    "(\\d+)?"                     // Optional verse number
                    // 8(
                    "(\\s*-\\s*"                  // Optionally start matching dash followed by end of the range
                      // 9( 10() )
                      "((\\d+)[:.])?"               // Optional chapter number followed by [:.]
                      // 11()
                      "(\\d+)?"                   // Optional verse number
                    // )
                    ")?"                          // End of matching end of range
                    "\\s*$"                       // Must match to end (ignore whitespace)
                    );
  Q_ASSERT(re.isValid());
  bool isValid = true;
  if (re.exactMatch(text))
  {
    QStringList cap = re.capturedTexts();
    // Get book name
    QString bookName;
    if (!cap[3].isEmpty())
    {
      bookName = cap[3];
    }
    else if (!cap[4].isEmpty())
    {
      bookName = cap[4];
    }
    if (!bookName.isEmpty())
    {
      int book = bookIndex(bookName);
      if (book >= 0)
      {
        key.start.book = book;
      }
      else
      {
        isValid = false;
      }
    }
    // Get chapter
    QString chapterName = cap[6];
    if (!chapterName.isEmpty())
    {
      int chapter = chapterName.toInt() - 1;
      if (chapter >= 0 && chapter < numChapters(key.start.book))
      {
        key.start.chapter = chapter;
      }
      else
      {
        isValid = false;
      }
    }
    // Get verse
    QString verseName = cap[7];
    if (!verseName.isEmpty())
    {
      int verse = verseName.toInt() - 1;
      if (verse >= 0 && verse < numVerses(key.start.book, key.start.chapter))
      {
        key.start.verse = verse;
      }
      else
      {
        isValid = false;
      }
    }
    // End of range
    if (!cap[8].isEmpty())
    {
      key.end.book = key.start.book;
      key.end.chapter = key.start.chapter;
      key.end.verse = -1;
      // Get chapter
      QString chapterName = cap[10];
      if (!chapterName.isEmpty())
      {
        int chapter = chapterName.toInt() - 1;
        if (chapter >= 0 && chapter < numChapters(key.start.book))
        {
          key.end.chapter = chapter;
        }
        else
        {
          isValid = false;
        }
      }
      // Get verse
      QString verseName = cap[11];
      if (!verseName.isEmpty())
      {
        int verse = verseName.toInt() - 1;
        if (verse >= 0 && verse < numVerses(key.start.book, key.start.chapter))
        {
          key.end.verse = verse;
        }
        else
        {
          isValid = false;
        }
      }
      if (key.end.verse < 0)
      {
        key.end.verse = numVerses(key.end.book, key.end.chapter)-1;
      }
    }
  }
  else
  {
    isValid = false;
  }
  //std::cout << "result: " << key.start.book << "." << key.start.chapter << ":" << key.start.verse << " - "
  //                        << key.end.book << "." << key.end.chapter << ":" << key.end.verse << std::endl;
  if (0 != valid)
  {
    *valid = isValid;
  }
  return key;
}

/// Create a key from individual values.
KwBibleModule::Key KwBibleModule::createKey(int book, int chapter, int verse)
{
  Key key = { { book, chapter, verse },
              { -1,   -1,      -1    } };
  return key;
}

/// Create a key from individual values.
KwBibleModule::Key KwBibleModule::createKey(const QString& book, int chapter, int verse)
{
  int bookId = bookIndex(book);
  Key key = { { bookId, chapter, verse },
              { -1,     -1,      -1    } };
  return key;
}

/// Create a range key between two verses in the same chapter.
KwBibleModule::Key KwBibleModule::createKey(const QString& book, int chapter, int verseStart,
                                                  int verseEnd)
{
  int bookId = bookIndex(book);
  Key key = { { bookId, chapter, verseStart },
              { bookId, chapter, verseEnd   } };
  return key;
}

/// Create a range key between two verses in different chapters.
KwBibleModule::Key KwBibleModule::createKey(const QString& book, int chapterStart, int verseStart,
                                                  int chapterEnd,   int verseEnd)
{
  int bookId = bookIndex(book);
  Key key = { { bookId, chapterStart, verseStart },
              { bookId, chapterEnd,   verseEnd   } };
  return key;
}

/// Create a range key between two verses in different books.
KwBibleModule::Key KwBibleModule::createKey(const QString& bookStart, int chapterStart, int verseStart,
                             const QString& bookEnd,   int chapterEnd,   int verseEnd)
{
  int bookIdStart = bookIndex(bookStart);
  int bookIdEnd = bookIndex(bookEnd);
  Key key = { { bookIdStart, chapterStart, verseStart },
              { bookIdEnd,   chapterEnd,   verseEnd   } };
  return key;
}

/// Is the text right to left?
bool KwBibleModule::isRightToLeft() const
{
  return m_rightToLeft;
}

/// List the books in this module.
const QStringList& KwBibleModule::books()
{
  if (m_books.isEmpty())
  {
    obtainBooks();
  }
  return m_books;
}

/// Get the index of a book from it's name.
int KwBibleModule::bookIndex(const QString& name)
{
  if (m_books.isEmpty())
  {
    obtainBooks();
  }
  return m_books.indexOf(name);
}

/// Get the name of a book from it's index.
QString KwBibleModule::bookName(int book)
{
  if (m_books.isEmpty())
  {
    obtainBooks();
  }
  if (book >= 0 && book < m_books.size())
  {
    return m_books[book];
  }
  else
  {
    return QString();
  }
}

bool KwBibleModule::fillPassage(const Key& key, KwBiblePassage* outPassage)
{
  Key range = key;

  // Complete the range
  if (range.start.book < 0)
  {
    // Start book must be specified
    return false;
  }
  else if (range.end.book < 0)
  {
    range.end.book = range.start.book;
  }

  if (range.start.chapter < 0)
  {
    range.start.chapter = 0;
    range.end.chapter = numChapters(range.end.book)-1;
  }
  else if (range.end.chapter < 0)
  {
    range.end.chapter = range.start.chapter;
  }

  if (range.start.verse < 0)
  {
    range.start.verse = 0;
    range.end.verse = numVerses(range.end.book, range.end.chapter)-1;
  }
  else if (range.end.verse < 0)
  {
    range.end.verse = range.start.verse;
  }

  outPassage->setSource(managerId(), name(), m_rightToLeft);
  outPassage->initBooks(range.start.book, 1+range.end.book-range.start.book);
  for (int book = range.start.book; book <= range.end.book; ++book)
  {
    bool isFirstBook = (book == range.start.book);
    bool isLastBook = (book == range.end.book);
    int maxChapters = numChapters(book);
    int firstChapter = (isFirstBook ? range.start.chapter : 0);
    int lastChapter = (isLastBook ? range.end.chapter : maxChapters-1);
    Q_ASSERT(lastChapter >= firstChapter && lastChapter < maxChapters);
    outPassage->initBook(book, bookName(book), 1+firstChapter, 1+lastChapter-firstChapter);
    for (int chapter = firstChapter; chapter <= lastChapter; ++chapter)
    {
      bool isFirstChapter = isFirstBook && (chapter == firstChapter);
      bool isLastChapter = isLastBook && (chapter == lastChapter);
      int maxVerses = numVerses(book, chapter);
      int firstVerse = (isFirstChapter ? range.start.verse : 0);
      int lastVerse = (isLastChapter ? range.end.verse : maxVerses-1);
      Q_ASSERT(lastVerse >= firstVerse && lastVerse < maxVerses);
      outPassage->initChapter(book, 1+chapter, 1+firstVerse, 1+lastVerse-firstVerse);
      for (int verse = firstVerse; verse <= lastVerse; ++verse)
      {
        fillPassageVerse(book, chapter, verse, outPassage);
      }
    }
  }
  return true;
}

/*
 * Protected virtual interface
 */

/// Ensure that the book list is up to date.
void KwBibleModule::obtainBooks()
{
}

/*
 * Protected interface
 */

/// Update the list of books.
void KwBibleModule::setBooks(const QStringList& books)
{
  m_books = books;
}

/// Set whether the module has text right-to-left.
void KwBibleModule::setRightToLeft(bool rightToLeft)
{
  m_rightToLeft = rightToLeft;
}

