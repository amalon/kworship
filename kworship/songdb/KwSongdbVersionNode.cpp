/**
 * @file KwSongdbVersionNode.cpp
 * @brief A node for a song version.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbVersionNode.h"

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwSongdbVersionNode::KwSongdbVersionNode(KwSongdbNode* parent, QString label, int id)
: KwSongdbNode(parent)
, m_label(label)
, m_id(id)
{
  if (m_label == "")
  {
    m_label = "Default version";
  }
}

/// Destructor.
KwSongdbVersionNode::~KwSongdbVersionNode()
{
}

/*
 * Main interface
 */

/// Get data associated with the node.
QVariant KwSongdbVersionNode::getData(int role, int column)
{
  if (role == Qt::DisplayRole)
  {
    if (column == 0)
    {
      return m_label;
    }
  }
  return QVariant();
}

/// Get flags for this item.
Qt::ItemFlags KwSongdbVersionNode::getFlags(Qt::ItemFlags defaultFlags) const
{
  return Qt::ItemIsDragEnabled | defaultFlags;
}

/// Get mime data string for this set of songs.
QString KwSongdbVersionNode::mimeData() const
{
  return QString("songdb %1").arg(m_id);
}

