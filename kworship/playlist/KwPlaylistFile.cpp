/**
 * @file KwPlaylistFile.h
 * @brief An image playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistFile.h"
#include "KwPlaylistFileNode.h"

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwPlaylistFile::KwPlaylistFile(const QUrl& url)
: KwPlaylistItem()
, m_url(url)
{
}

/// Destructor.
KwPlaylistFile::~KwPlaylistFile()
{
}

/*
 * Main interface.
 */

KwPlaylistNode* KwPlaylistFile::getNode(KwPlaylistNode* parent)
{
  return new KwPlaylistFileNode(parent, this);
}

/// Activate the file.
void KwPlaylistFile::activate(KwDisplayManager*)
{
}

/*
 * Accessors
 */

/// Get the image url.
QUrl KwPlaylistFile::getUrl() const
{
  return m_url;
}

