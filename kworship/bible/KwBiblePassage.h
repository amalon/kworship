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

#ifndef _KwBiblePassage_h_
#define _KwBiblePassage_h_

/**
 * @file KwBiblePassage.h
 * @brief A passage of rendered bible text.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBibleModule.h"

#include <QString>

/** A passage of rendered bible text.
 * Stores enough information to adjust settings.
 * Can be used as a cache.
 */
class KwBiblePassage
{
  public:
    
    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwBiblePassage();

    /// Destructor.
    virtual ~KwBiblePassage();

    /*
     * Main interface
     */

    /** Clear the passage.
     * Deletes all books.
     */
    void clear();

    /** Set the source module.
     * @param managerId ID of the bible manager.
     * @param moduleId ID of the bible module.
     */
    void setSource(const QString& managerId, const QString& moduleId);

    /** Initialise the books in the passage.
     * If books are already initialised they will be cleared first.
     * @param firstBook Number of first book in passage.
     * @param numBooks Number of books covered in this passage.
     * @param numBooks > 0
     */
    void initBooks(int firstBook, int numBooks);

    /** Initialise a book in the passage.
     * If the book is already initialised it will be cleared first.
     * @param bookNumber Number of the book to initialise.
     * @param name Name of the book.
     * @param firstChapter Number of first chapter in book.
     * @param numChapters Number of chapters covered in this book.
     * @pre firstBookNumber() <= bookNumber <= lastBookNumber()
     * @pre numChapters > 0
     */
    void initBook(int bookNumber,
                  const QString& name, int firstChapter, int numChapters);

    /** Initialise a chapter in the passage.
     * If the chapter is already initialised it will be cleared first.
     * @param bookNumber Number of the book with the chapter to initialise.
     * @param chapterNumber Number of the chapter to initialise.
     * @param firstVerse Number of first verse in chapter.
     * @param numVerses Number of verses covered in this chapter.
     * @pre firstBookNumber() <= bookNumber <= lastBookNumber()
     * @pre firstChapterNumber(bookNumber) <= chapterNumber <= lastChapterNumber(bookNumber)
     * @pre numVerses > 0
     */
    void initChapter(int bookNumber, int chapterNumber,
                     int firstVerse, int numVerses);

    /** Initialise a verse in the passage.
     * If the verse is already initialised it will be cleared first.
     * @param bookNumber Number of the book with the chapter to initialise.
     * @param chapterNumber Number of the chapter with the verse to initialise.
     * @param verseNumber Number of the verse to initialise.
     * @param headings Headings HTML preceeding this verse.
     * @param content Main HTML in this verse.
     * @pre firstBookNumber() <= bookNumber <= lastBookNumber()
     * @pre firstChapterNumber(bookNumber) <= chapterNumber <= lastChapterNumber(bookNumber)
     * @pre firstVerseNumber(bookNumber) <= verseNumber <= lastVerseNumber(bookNumber)
     */
    void initVerse(int bookNumber, int chapterNumber, int verseNumber,
                   const QString& headings, const QString& content);

    /*
     * Accessors
     */

    /// Find whether the passage is empty.
    bool isEmpty() const;

    /// Get textual key of this passage.
    QString textualKey() const;

    /// Get the first book number in the passage.
    int firstBookNumber() const;
    /// Get the last book number in the passage.
    int lastBookNumber() const;

    /** Get the first chapter number in a book of the passage.
     * @param bookNumber The number of the book.
     * @pre firstBookNumber() <= bookNumber <= lastBookNumber()
     */
    int firstChapterNumber(int bookNumber) const;
    /** Get the last chapter number in a book of the passage.
     * @param bookNumber The number of the book.
     * @pre firstBookNumber() <= bookNumber <= lastBookNumber()
     */
    int lastChapterNumber(int bookNumber) const;

    /** Get the first verse number in a chapter of the passage.
     * @param bookNumber The number of the book.
     * @param chapterNumber The number of the chapter within the book.
     * @pre firstBookNumber() <= bookNumber <= lastBookNumber()
     * @pre firstChapterNumber(bookNumber) <= chapterNumber <= lastChapterNumber(bookNumber)
     */
    int firstVerseNumber(int bookNumber, int chapterNumber) const;
    /** Get the last verse number in a chapter of the passage.
     * @param bookNumber The number of the book.
     * @param chapterNumber The number of the chapter within the book.
     * @pre firstBookNumber() <= bookNumber <= lastBookNumber()
     * @pre firstChapterNumber(bookNumber) <= chapterNumber <= lastChapterNumber(bookNumber)
     */
    int lastVerseNumber(int bookNumber, int chapterNumber) const;

    /*
     * Text extraction
     */

    /// Get the entire passaage rendered as HTML.
    /// @todo Needs some rendering options, headings, footnotes etc.
    QString renderedText();

  private:

    /*
     * Types
     */

    /// A verse in a chapter in a book.
    struct Verse
    {
      /// The headings preceeding this verse.
      QString headings;
      /// The main HTML content of this verse.
      QString content;
      /// @todo Footnotes
    };

    /// A chapter in a book containing verses.
    struct Chapter
    {
      /// The number of the first verse in this chapter.
      int firstVerse;
      /// The number of verses in this chapter.
      int numVerses;
      /// The array of verses.
      Verse* verses;
    };

    /// A book containing chapters.
    struct Book
    {
      /// The name of this book.
      QString name;
      /// The number of the first chapter in this book.
      int firstChapter;
      /// The number of chapters in this book.
      int numChapters;
      /// The array of chapters.
      Chapter* chapters;
    };

    /*
     * Variables
     */

    /// Bible manager id.
    QString m_managerId;
    /// Bible module id.
    QString m_moduleId;
    /// Original module key.
    KwBibleModule::Key m_key;

    /// The number of the first book.
    int m_firstBook;
    /// The number of books.
    int m_numBooks;
    /// The array of books.
    Book* m_books;
};

#endif // _KwBiblePassage_h_

