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

#ifndef _KwBibleModuleBibleGateway_h_
#define _KwBibleModuleBibleGateway_h_

/**
 * @file KwBibleModuleBibleGateway.h
 * @brief A BibleGateway bible module.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBibleModule.h"

#include <KUrl>

#include <QList>

/// A BibleGateway bible module.
class KwBibleModuleBibleGateway : public KwBibleModule
{
  public:
    
    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwBibleModuleBibleGateway(QString url);

    /// Destructor.
    virtual ~KwBibleModuleBibleGateway();

    /*
     * Main interface
     */

    // Reimplemented
    virtual QString name();

    // Reimplemented
    virtual QString description();

    // Reimplemented
    virtual QString managerId();

    // Reimplemented
    virtual int numChapters(int book);

    // Reimplemented
    virtual int numVerses(int book, int chapter);

    // Reimplemented
    virtual bool fillPassageVerse(int bookIndex, int chapterIndex, int verseIndex, KwBiblePassage* outPassage);

  protected:

    /*
     * Protected virtual interface
     */

    // Reimplemented
    virtual void obtainBooks();

  private:

    /*
     * Private functions
     */

    struct Chapter;

    /// Ensure chapter contents are fetched and return the chapter object.
    struct Chapter* fetchChapter(int book, int chapter);

    /*
     * Variables
     */

    /// The name of the publisher.
    QString m_publisher;

    /// The long version information.
    QString m_versionInfo;

    /// The long copyright information.
    QString m_copyrightInfo;

    /// Verse data.
    struct Verse
    {
      /// Headings preceeding verse.
      QString heading;

      /// Content of verse.
      QString content;
    };

    /// Chapter data.
    struct Chapter
    {
      /// BibleGateway.com URL for this chapter.
      KUrl url;

      /// Whether the verses have been fetched.
      bool fetched;

      /// List of verse contents.
      QList<Verse> verses;
    };

    /// Book data.
    struct Book
    {
      /// Name of the book.
      QString name;

      /// List of chapter information.
      QList<Chapter> chapters;
    };

    /// List of books.
    QList<Book> m_bookList;
};

#endif // _KwBibleModuleBibleGateway_h_

