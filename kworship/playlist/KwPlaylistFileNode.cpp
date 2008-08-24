/**
 * @file KwPlaylistFileNode.cpp
 * @brief A playlist node for a file.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistFileNode.h"
#include "KwPlaylistFile.h"

#include <KMimeType>
#include <KIcon>

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistFileNode::KwPlaylistFileNode(KwPlaylistNode* parent, KwPlaylistFile* item)
: KwPlaylistNode(parent)
, m_item(item)
{
}

/// Destructor.
KwPlaylistFileNode::~KwPlaylistFileNode()
{
}

/*
 * Main interface
 */

QVariant KwPlaylistFileNode::getData(int role, int column)
{
  if (role == Qt::DisplayRole)
  {
    if (column == 0)
    {
      return m_item->getUrl();
    }
  }
  else if (role == Qt::DecorationRole)
  {
    if (column == 0)
    {
      KSharedPtr<KMimeType> mimeType = KMimeType::findByUrl(m_item->getUrl());
      return KIcon(mimeType->iconName());
    }
  }
  return QVariant();
}

void KwPlaylistFileNode::activate(KwDisplayManager* manager)
{
  m_item->activate(manager);
}

