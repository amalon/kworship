/**
 * @file KwPlaylistModel.cpp
 * @brief A Qt model for playlist items.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistModel.h"

#include <cassert>

/*
 * Constructors + destructor.
 */

/// Default constructor.
KwPlaylistModel::KwPlaylistModel(QObject* parent)
: QAbstractItemModel(parent)
, m_root(0)
{
}

/// Destructor.
KwPlaylistModel::~KwPlaylistModel()
{
  delete m_root;
}

/*
 * Main interface
 */

/// Set the root node.
void KwPlaylistModel::setRootNode(KwPlaylistNode* root)
{
  delete m_root;
  m_root = root;
  reset();
}

KwPlaylistNode* KwPlaylistModel::itemFromIndex(const QModelIndex& index) const
{
  if (index.isValid()) {
    return reinterpret_cast<KwPlaylistNode*>(index.internalPointer());
  } else {
    return m_root;
  }
}

QModelIndex KwPlaylistModel::index(int row, int column, const QModelIndex& parent) const
{
  if (0 == m_root)
  {
    return QModelIndex();
  }
  KwPlaylistNode* parentNode = itemFromIndex(parent);
  assert(0 != parentNode);
  return createIndex(row, column, parentNode->getChild(row));
}

QModelIndex KwPlaylistModel::parent(const QModelIndex& child) const
{
  KwPlaylistNode* node = itemFromIndex(child);
  assert(0 != node);
  KwPlaylistNode* parentNode = node->getParent();
  if (0 == parentNode)
  {
    return QModelIndex();
  }
  KwPlaylistNode* grandParentNode = parentNode->getParent();
  if (0 == grandParentNode)
  {
    return QModelIndex();
  }
  int row = grandParentNode->getChildIndex(parentNode);
  assert(row != -1);
  return createIndex(row, child.column(), parentNode);
}

int KwPlaylistModel::rowCount(const QModelIndex& parent) const
{
  KwPlaylistNode* parentNode = itemFromIndex(parent);
  if (0 == parentNode)
  {
    return 0;
  }
  return parentNode->getChildCount();
}

int KwPlaylistModel::columnCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);
  return 2;
}

QVariant KwPlaylistModel::data(const QModelIndex& index, int role) const
{
  KwPlaylistNode* item = itemFromIndex(index);
  if (0 == item)
  {
    return QVariant();
  }
  return item->getData(role, index.column());

}

QVariant KwPlaylistModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
  {
    if (section == 0)
    {
      return tr("Node");
    }
    else if (section == 1)
    {
      return tr("Value");
    }
  }
  return QVariant();
}

