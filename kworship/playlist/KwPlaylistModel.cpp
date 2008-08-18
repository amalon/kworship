/**
 * @file KwPlaylistModel.cpp
 * @brief A Qt model for playlist items.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistModel.h"

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

QModelIndex KwPlaylistModel::index(int row, int column, const QModelIndex& parent) const
{
  if (!m_root)
  {
    return QModelIndex();
  }
  KwPlaylistNode* parentNode = itemFromIndex(parent);
  return createIndex(row, column, parentNode->getChild(row));
}

QModelIndex KwPlaylistModel::parent(const QModelIndex &child) const
{
/*  KwPlaylistNode *node = itemFromIndex(child);
  if (!node)
  {
    return QModelIndex();
  }
  KwPlaylistNode *parentNode = node->parent;
  if (!parentNode)
  {
    return QModelIndex();
  }
  KwPlaylistNode *grandparentNode = parentNode->parent;
  if (!grandparentNode)
  {
    return QModelIndex();
  }
  int row = grandparentNode->children.indexOf(parentNode);
  return createIndex(row, child.column(), parentNode);
  */
  return QModelIndex();
}

int KwPlaylistModel::rowCount(const QModelIndex &parent) const
{
  KwPlaylistNode *parentNode = itemFromIndex(parent);
  if (!parentNode)
  {
    return 0;
  }
  return parentNode->getChildCount();
}

int KwPlaylistModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return 2;
}

QVariant KwPlaylistModel::data(const QModelIndex &index, int role) const
{
  KwPlaylistNode *item = itemFromIndex(index);
  if (!item)
  {
    return QVariant();
  }
  return item->getData(role, index.column());

}

QVariant KwPlaylistModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  /*
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
  */
  return QVariant();
}

/*
 * Private helpers
 */

KwPlaylistNode* KwPlaylistModel::itemFromIndex(const QModelIndex &index) const
{
  if (index.isValid()) {
    return reinterpret_cast<KwPlaylistNode*>(index.internalPointer());
  } else {
    return m_root;
  }
}


