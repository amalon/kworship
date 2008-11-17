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

    /// Fill the passage from a given module.
    KwBiblePassage(const QString& managerId, const QString& moduleId, const KwBibleModule::Key& key);

    /// Destructor.
    virtual ~KwBiblePassage();

    /*
     * Main interface
     */

    /// Get textual key of this passage.
    QString textualKey() const;

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

