/**
 * @file KwPlaylistPaged.cpp
 * @brief A plain paged playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistPaged.h"
#include "KwPlaylistPagedNode.h"
#include "compiler.h"

#include <cassert>

/*
 * Constructors + destructor.
 */

/// Default constructor.
KwPlaylistPaged::KwPlaylistPaged()
: KwPlaylistItem()
, m_pageContents()
, m_blockStarts()
{
}

/// Destructor.
KwPlaylistPaged::~KwPlaylistPaged()
{
}

/*
 * Main interface
 */

/// Get the number of text blocks.
unsigned int KwPlaylistPaged::getBlockCount() const
{
  return m_blockStarts.size();
}

/// Get the number of pages.
unsigned int KwPlaylistPaged::getPageCount() const
{
  return m_pageContents.size();
}

/// Get a block's first page number.
unsigned int KwPlaylistPaged::getBlockPageIndex(unsigned int blockIndex) const
{
  assert(blockIndex < getBlockCount());
  return m_blockStarts[blockIndex];
}

/// Get the number of pages in a block.
unsigned int KwPlaylistPaged::getBlockPageCount(unsigned int blockIndex) const
{
  assert(blockIndex < getBlockCount());
  if (likely(blockIndex < getBlockCount()-1))
  {
    return getBlockPageIndex(blockIndex+1) - getBlockPageIndex(blockIndex);
  }
  else
  {
    return getPageCount() - getBlockPageIndex(blockIndex);
  }
}

/// Get a page's block index.
unsigned int KwPlaylistPaged::getPageBlockIndex(unsigned int pageIndex) const
{
  assert(pageIndex < getPageCount());
  for (unsigned int block = 1; block < getBlockCount(); ++block)
  {
    if (getBlockPageIndex(block) >= pageIndex)
    {
      return block - 1;
    }
  }
  return getBlockCount() - 1;
}

/// Get the content of a page.
QString KwPlaylistPaged::getPageText(unsigned int pageIndex) const
{
  return m_pageContents[pageIndex];
}

KwPlaylistNode* KwPlaylistPaged::getNode(KwPlaylistNode* parent)
{
  return new KwPlaylistPagedNode(parent, this);
}

/*
 * Derived class block control interface
 */

/// Set the text blocks.
void KwPlaylistPaged::setTextBlocks(const QStringList& blocks)
{
  m_pageContents = blocks;
  m_blockStarts.resize(blocks.size());
  for (int block = 0; block < blocks.size(); ++block)
  {
    m_blockStarts[block] = block;
  }
}

