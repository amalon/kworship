/**
 * @file KwPlaylistPagedNodePage.cpp
 * @brief A playlist node for a paged text item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistPagedNodePage.h"
#include "KwPlaylistPaged.h"

#include "KwDisplayManager.h"

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistPagedNodePage::KwPlaylistPagedNodePage(KwPlaylistNode* parent, KwPlaylistPaged* item, unsigned int page)
: KwPlaylistNode(parent)
, m_item(item)
, m_page(page)
{
}

/// Destructor.
KwPlaylistPagedNodePage::~KwPlaylistPagedNodePage()
{
}

/*
 * Main interface
 */

QVariant KwPlaylistPagedNodePage::getData(int role, int column)
{
  if (role == Qt::DisplayRole)
  {
    if (column == 0)
    {
      return m_item->getPageText(m_page);
    }
  }
  return QVariant();
}

void KwPlaylistPagedNodePage::activate(KwDisplayManager* manager)
{
  manager->applyStyles(m_item);
  // Set text
  manager->text.setText(m_item->getPageText(m_page));
}

