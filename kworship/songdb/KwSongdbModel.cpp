/**
 * @file KwSongdbModel.cpp
 * @brief A Qt model for songs in the database.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbModel.h"
#include "KwSongdbNode.h"

#include <cassert>

/*
* Constructors + destructor.
*/

/// Default constructor.
KwSongdbModel::KwSongdbModel(QObject* parent)
: QAbstractItemModel(parent)
, m_root(0)
{
}

/// Destructor.
KwSongdbModel::~KwSongdbModel()
{
  delete m_root;
}

/*
* Main interface
*/

/// Set the root node.
void KwSongdbModel::setRootNode(KwSongdbNode* root)
{
  delete m_root;
  m_root = root;
  reset();
}

KwSongdbNode* KwSongdbModel::itemFromIndex(const QModelIndex &index) const
{
  if (index.isValid()) {
    return reinterpret_cast<KwSongdbNode*>(index.internalPointer());
  } else {
    return m_root;
  }
}

QModelIndex KwSongdbModel::index(int row, int column, const QModelIndex& parent) const
{
  if (0 == m_root)
  {
    return QModelIndex();
  }
  KwSongdbNode* parentNode = itemFromIndex(parent);
  assert(0 != parentNode);
  return createIndex(row, column, parentNode->getChild(row));
}

QModelIndex KwSongdbModel::parent(const QModelIndex &child) const
{
  KwSongdbNode* node = itemFromIndex(child);
  assert(0 != node);
  KwSongdbNode* parentNode = node->getParent();
  if (0 == parentNode)
  {
    return QModelIndex();
  }
  KwSongdbNode* grandParentNode = parentNode->getParent();
  if (0 == grandParentNode)
  {
    return QModelIndex();
  }
  int row = grandParentNode->getChildIndex(parentNode);
  assert(row != -1);
  return createIndex(row, child.column(), parentNode);
}

int KwSongdbModel::rowCount(const QModelIndex &parent) const
{
  KwSongdbNode* parentNode = itemFromIndex(parent);
  if (0 == parentNode)
  {
    return 0;
  }
  return parentNode->getChildCount();
}

int KwSongdbModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return 1;
}

QVariant KwSongdbModel::data(const QModelIndex &index, int role) const
{
  KwSongdbNode* item = itemFromIndex(index);
  if (0 == item)
  {
    return QVariant();
  }
  return item->getData(role, index.column());
}

QVariant KwSongdbModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  Q_UNUSED(section)
  Q_UNUSED(orientation)
  Q_UNUSED(role)
  return QVariant();
}

Qt::ItemFlags KwSongdbModel::flags(const QModelIndex& index) const
{
  Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

  KwSongdbNode* item = itemFromIndex(index);
  if (0 != item)
  {
    return item->getFlags(defaultFlags);
  }
  else
  {
    return defaultFlags;
  }
}

