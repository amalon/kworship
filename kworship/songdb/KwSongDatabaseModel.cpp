/**
 * @file KwSongDatabaseModel.cpp
 * @brief A Qt model for songs in the database.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongDatabaseModel.h"
#include "KwSongDatabaseNode.h"

#include <cassert>

/*
* Constructors + destructor.
*/

/// Default constructor.
KwSongDatabaseModel::KwSongDatabaseModel(QObject* parent)
: QAbstractItemModel(parent)
, m_root(0)
{
}

/// Destructor.
KwSongDatabaseModel::~KwSongDatabaseModel()
{
  delete m_root;
}

/*
* Main interface
*/

/// Set the root node.
void KwSongDatabaseModel::setRootNode(KwSongDatabaseNode* root)
{
  delete m_root;
  m_root = root;
  reset();
}

KwSongDatabaseNode* KwSongDatabaseModel::itemFromIndex(const QModelIndex &index) const
{
  if (index.isValid()) {
    return reinterpret_cast<KwSongDatabaseNode*>(index.internalPointer());
  } else {
    return m_root;
  }
}

QModelIndex KwSongDatabaseModel::index(int row, int column, const QModelIndex& parent) const
{
  if (0 == m_root)
  {
    return QModelIndex();
  }
  KwSongDatabaseNode* parentNode = itemFromIndex(parent);
  assert(0 != parentNode);
  return createIndex(row, column, parentNode->getChild(row));
}

QModelIndex KwSongDatabaseModel::parent(const QModelIndex &child) const
{
  KwSongDatabaseNode* node = itemFromIndex(child);
  assert(0 != node);
  KwSongDatabaseNode* parentNode = node->getParent();
  if (0 == parentNode)
  {
    return QModelIndex();
  }
  KwSongDatabaseNode* grandParentNode = parentNode->getParent();
  if (0 == grandParentNode)
  {
    return QModelIndex();
  }
  int row = grandParentNode->getChildIndex(parentNode);
  assert(row != -1);
  return createIndex(row, child.column(), parentNode);
}

int KwSongDatabaseModel::rowCount(const QModelIndex &parent) const
{
  KwSongDatabaseNode* parentNode = itemFromIndex(parent);
  if (0 == parentNode)
  {
    return 0;
  }
  return parentNode->getChildCount();
}

int KwSongDatabaseModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return 1;
}

QVariant KwSongDatabaseModel::data(const QModelIndex &index, int role) const
{
  KwSongDatabaseNode* item = itemFromIndex(index);
  if (0 == item)
  {
    return QVariant();
  }
  return item->getData(role, index.column());
}

QVariant KwSongDatabaseModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  Q_UNUSED(section)
  Q_UNUSED(orientation)
  Q_UNUSED(role)
  return QVariant();
}

