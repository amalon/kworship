/**
 * @file KwPlaylistText.cpp
 * @brief A plain text playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistText.h"
#include "KwPlaylistTextNode.h"

/*
 * Constructors + destructor.
 */

/// Default constructor.
KwPlaylistText::KwPlaylistText(const QString& label, const QStringList& blocks)
: KwPlaylistPaged()
, m_label(label)
{
  setTextBlocks(blocks);
}

/// Destructor.
KwPlaylistText::~KwPlaylistText()
{
}

/*
 * Main interface
 */

/// Get the label.
QString KwPlaylistText::getLabel() const
{
  return m_label;
}

KwPlaylistNode* KwPlaylistText::getNode(KwPlaylistNode* parent)
{
  return new KwPlaylistTextNode(parent, this);
}

