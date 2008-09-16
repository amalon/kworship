#ifndef _KwSongDatabaseNode_h_
#define _KwSongDatabaseNode_h_

/**
 * @file KwSongDatabaseNode.h
 * @brief A node on a song database tree.
 * @author James Hogan <james@albanarts.com>
 */

#include <QVariant>
#include <QVector>

class KwDisplayManager;

/// A node on a playlist tree.
/**
 * Inherit from this class for each playlist node type.
 */
class KwSongDatabaseNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwSongDatabaseNode(KwSongDatabaseNode* parent);

    /// Destructor.
    virtual ~KwSongDatabaseNode();

    /*
     * Main interface
     */

    /// Get the parent.
    KwSongDatabaseNode* getParent();

    /// Get a child node by index.
    KwSongDatabaseNode* getChild(int index);

    /// Get the index of a certain child.
    int getChildIndex(KwSongDatabaseNode* node) const;

    /// Get data associated with the node.
    virtual QVariant getData(int role, int column);

    /// Get the number of children.
    virtual int getChildCount() const;

    /// Activate the node using a display manager.
    virtual void activate(KwDisplayManager* manager);

  protected:

    /// Get a child node by index.
    virtual KwSongDatabaseNode* _getChild(int index);

  private:

    /*
     * Variables
     */

    /// Parent node.
    KwSongDatabaseNode* m_parent;

    /// Child nodes.
    QVector<KwSongDatabaseNode*> m_children;
};

#endif // _KwSongDatabaseNode_h_

