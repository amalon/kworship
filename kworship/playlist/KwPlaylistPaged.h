#ifndef _KwPlaylistPaged_h_
#define _KwPlaylistPaged_h_

/**
 * @file KwPlaylistPaged.h
 * @brief A paged plain text playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistItem.h"

#include <QStringList>
#include <QVector>

/// A paged plain text playlist item.
class KwPlaylistPaged : public KwPlaylistItem
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

