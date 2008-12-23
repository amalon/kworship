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

#ifndef _KwBibleModuleSword_h_
#define _KwBibleModuleSword_h_

/**
 * @file KwBibleModuleSword.h
 * @brief A SWORD bible module.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBibleModule.h"

namespace sword
{
  class SWText;
}

/// A SWORD bible module.
class KwBibleModuleSword : public KwBibleModule
{
  public:
    
    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwBibleModuleSword(sword::SWText* module);

    /// Destructor.
    virtual ~KwBibleModuleSword();

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

    /*
     * Internal functions
     */

    /** Convert a local book index to a bible book index.
     * @param localIndex Local index of book in module.
     * @returns Index of the book in the bible.
     */
    int localToBible(int localIndex) const;

    /** Convert a bible book index to a local book index.
     * @param bibleIndex Index of book in bible.
     * @returns Local index of book in module.
     */
    int bibleToLocal(int bibleIndex) const;

    /** Convert a testament & book number to a bible book index.
     * @param testament Testament number [0,1].
     * @param book Book number [0,..].
     * @returns Bible book index.
     */
    int testamentBookToBible(int testament, int book) const;

    /** Convert a bible book index into a testament and book number.
     * @param bibleIndex Bible book index.
     * @param book[out] Points to int in which to write book number.
     * @returns Which testament [0,1].
     */
    int bibleToTestamentBook(int bibleIndex, int* book) const;

    /** Convert a testament & book number to a local book index.
     * @param testament Testament number [0,1].
     * @param book Book number [0,..].
     * @returns Local book index.
     */
    int testamentBookToLocal(int testament, int book) const;

    /** Convert a local book index into a testament and book number.
     * @param localIndex Local book index.
     * @param book[out] Points to int in which to write book number.
     * @returns Which testament [0,1].
     */
    int localToTestamentBook(int localIndex, int* book) const;

  private:

    /*
     * Variables
     */
    
    /// SWORD module object.
    sword::SWText* m_module;

    /// First book of the bible in this module.
    int m_firstBibleBookIndex;

    /// Last book of the bible in this module.
    int m_lastBibleBookIndex;
};

#endif // _KwBibleModuleSword_h_

