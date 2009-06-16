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

#ifndef _KwPlaylistPaged_h_
#define _KwPlaylistPaged_h_

/**
 * @file KwPlaylistPaged.h
 * @brief A paged plain text playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistItem.h"

#include <KwExport.h>

#include <QStringList>
#include <QVector>

/// A paged plain text playlist item.
class KWMAIN_EXPORT KwPlaylistPaged : public KwPlaylistItem
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Default constructor.
    KwPlaylistPaged();

    /// Destructor.
    virtual ~KwPlaylistPaged();

    /*
     * Main interface
     */

    /// Get the number of text blocks.
    unsigned int getBlockCount() const;

    /// Get the number of pages.
    unsigned int getPageCount() const;

    /// Get a block's first page number.
    unsigned int getBlockPageIndex(unsigned int blockIndex) const;

    /// Get the number of pages in a block.
    unsigned int getBlockPageCount(unsigned int blockIndex) const;

    /// Get a page's block index.
    unsigned int getPageBlockIndex(unsigned int pageIndex) const;

    /// Get the content of a page.
    QString getPageText(unsigned int pageIndex) const;

    /// Get the list of blocks.
    QStringList blocks() const;

    virtual KwPlaylistNode* getNode(KwPlaylistNode* parent);

  protected:

    /*
     * Derived class block control interface
     */

    /// Set the text blocks.
    void setTextBlocks(const QStringList& blocks);

  private:

    /*
     * Variables
     */

    /// Contents of the pages.
    QStringList m_pageContents;

    /// Starting page index of each block.
    QVector<unsigned int> m_blockStarts;
};

#endif // _KwPlaylistPaged_h_

