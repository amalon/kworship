#ifndef _KwPlaylistNode_h_
#define _KwPlaylistNode_h_

/**
 * @file KwPlaylistNode.h
 * @brief A node on a playlist tree.
 * @author James Hogan <james@albanarts.com>
 */

#include <QVariant>
#include <QVector>

class KwDisplayManager;

/// A node on a playlist tree.
/**
 * Inherit from this class for each playlist node type.
 */
class KwPlaylistNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistNode(KwPlaylistNode* parent);

    /// Destructor.
    virtual ~KwPlaylistNode();

    /*
     * Main interface
     */

    /// Get the parent.
    KwPlaylistNode* getParent();

    /// Get a child node by index.
    KwPlaylistNode* getChild(int index);

    /// Get the index of a certain child.
    int getChildIndex(KwPlaylistNode* node) const;

    /// Get data associated with the node.
    virtual QVariant getData(int role, int column);

    /// Get the number of children.
    virtual int getChildCount() const;

    /// Activate the node using a display manager.
    virtual void activate(KwDisplayManager* manager);

  protected:

    /// Get a child node by index.
    virtual KwPlaylistNode* _getChild(int index);

  private:

    /*
     * Variables
     */

    /// Parent node.
    KwPlaylistNode* m_parent;

    /// Child nodes.
    QVector<KwPlaylistNode*> m_children;
};

#endif // _KwPlaylistNode_h_

