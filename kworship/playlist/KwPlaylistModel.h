#ifndef _KwPlaylistModel_h_
#define _KwPlaylistModel_h_

/**
 * @file KwPlaylistModel.h
 * @brief A Qt model for playlist items.
 * @author James Hogan <james@albanarts.com>
 */

#include <QAbstractItemModel>

class KwPlaylistNode;

/// A Qt model for playlist items.
class KwPlaylistModel : public QAbstractItemModel
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Default constructor.
    KwPlaylistModel(QObject* parent = 0);

    /// Destructor.
    virtual ~KwPlaylistModel();

    /*
     * Main interface
     */

    /// Set the root node.
    void setRootNode(KwPlaylistNode* root);
    KwPlaylistNode* itemFromIndex(const QModelIndex &index) const;

    QModelIndex index(int row, int column, const QModelIndex& parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    // Drag and drop
    QStringList mimeTypes() const;
    Qt::DropActions supportedDropActions() const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
    bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent);

  private:

    /*
     * Variables
     */

    /// Root item.
    KwPlaylistNode* m_root;
};

#endif // _KwPlaylistModel_h_

