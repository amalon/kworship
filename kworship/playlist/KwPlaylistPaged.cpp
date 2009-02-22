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

/// Get the list of blocks.
QStringList KwPlaylistPaged::blocks() const
{
  QStringList result;
  for (int block = 0; block < m_blockStarts.size(); ++block)
  {
    unsigned int first = m_blockStarts[block];
    unsigned int count = (block == m_blockStarts.size()-1 ? -1 : m_blockStarts[block+1]-first);
    result += QStringList(m_pageContents.mid(first, count)).join("\n");
  }
  return result;
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

