#ifndef _KwSongDatabaseModel_h_
#define _KwSongDatabaseModel_h_

/**
 * @file KwSongDatabaseModel.h
 * @brief A Qt model for songs in the database.
 * @author James Hogan <james@albanarts.com>
 */

#include <QAbstractItemModel>

class KwSongDatabaseNode;

/// A Qt model for playlist items.
class KwSongDatabaseModel : public QAbstractItemModel
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Default constructor.
    KwSongDatabaseModel(QObject* parent = 0);

    /// Destructor.
    virtual ~KwSongDatabaseModel();

    /*
     * Main interface
     */

    /// Set the root node.
    void setRootNode(KwSongDatabaseNode* root);
    KwSongDatabaseNode* itemFromIndex(const QModelIndex &index) const;

    QModelIndex index(int row, int column, const QModelIndex& parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;


  private:

    /*
     * Variables
     */

    /// Root item.
    KwSongDatabaseNode* m_root;
};

#endif // _KwSongDatabaseModel_h_

