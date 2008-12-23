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

#ifndef _KwBibleModule_h_
#define _KwBibleModule_h_

/**
 * @file KwBibleModule.h
 * @brief An abstract bible module (analagous to a SWORD module).
 * @author James Hogan <james@albanarts.com>
 */

#include <QString>
#include <QStringList>

class KwBiblePassage;

/// A bible module (analagous to a SWORD module).
class KwBibleModule
{
  public:

    /*
     * Types
     */

    /// Verse key.
    struct VerseKey
    {
      /// Book of the bible.
      int book;
      /// Chapter of the book (-1 for entire book).
      int chapter;
      /// Verse of the chapter (-1 for entire chapter).
      int verse;
    };

    /// Range of verse keys.
    struct Key
    {
      /// Start key of range.
      VerseKey start;
      /// End key of range.
      VerseKey end;
    };
    
    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwBibleModule();

    /// Destructor.
    virtual ~KwBibleModule();

    /*
     * Main interface
     */

    /// Create a key from a string.
    Key createKey(const QString& text, bool* valid = 0);

    /// Create a key from a string relative to another key.
    Key createKey(const Key& other, const QString& text, bool* valid = 0);

    /// Create a key from individual values.
    Key createKey(int book, int chapter, int verse = -1);

    /// Create a key from individual values.
    Key createKey(const QString& book, int chapter, int verse = -1);

    /// Create a range key between two verses in the same chapter.
    Key createKey(const QString& book, int chapter, int verseStart,
                                                    int verseEnd);

    /// Create a range key between two verses in different chapters.
    Key createKey(const QString& book, int chapterStart, int verseStart,
                                       int chapterEnd,   int verseEnd);

    /// Create a range key between two verses in different books.
    Key createKey(const QString& bookStart, int chapterStart, int verseStart,
                  const QString& bookEnd,   int chapterEnd,   int verseEnd);

    /// Get the name of the module.
    virtual QString name() = 0;

    /// Get the description of the module.
    virtual QString description() = 0;

    /// Get the id of the manager for this module.
    virtual QString managerId() = 0;

    /// Is the text right to left?
    bool isRightToLeft() const;

    /// List the books in this module.
    const QStringList& books();

    /** Get the index of a book from it's name.
     * @param name Name of the book to look for.
     * @return Index of the book in this module or -1 if it does not exist.
     */
    int bookIndex(const QString& name);

    /// Get the name of a book from it's index.
    QString bookName(int book);

    /// Get the number of chapters in this book.
    virtual int numChapters(int book) = 0;

    /// Get the number of verses in a chapter of a book.
    virtual int numVerses(int book, int chapter) = 0;

    /// Fill a passage object.
    bool fillPassage(const Key& key, KwBiblePassage* outPassage);

    /// Fill a single verse with data.
    virtual bool fillPassageVerse(int bookIndex, int chapterIndex, int verseIndex, KwBiblePassage* outPassage) = 0;

  protected:

    /*
     * Protected virtual interface
     */

    /// Ensure that the book list is up to date.
    virtual void obtainBooks();

    /*
     * Protected interface
     */

    /// Update the list of books.
    void setBooks(const QStringList& books);

    /// Set whether the module has text right-to-left.
    void setRightToLeft(bool rightToLeft);

  private:

    /*
     * Variables
     */

    /// List of book names.
    QStringList m_books;

    /// Whether the module has text right to left.
    bool m_rightToLeft;

};

#endif // _KwBibleModule_h_

