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

/*
 * Constructors + destructor
 */

/// Default constructor.
KwBibleModule::KwBibleModule()
: m_books()
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
KwBibleModule::Key KwBibleModule::createKey(const QString& text)
{
  // parse the key
  //Key key = { { -1, -1, -1 },
  //            { -1, -1, -1 } };
  Key key = { { 0, 1, 1 },
              { 0, 1, 6 } };
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

