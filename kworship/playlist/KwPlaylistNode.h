#ifndef _KwPlaylistNode_h_
#define _KwPlaylistNode_h_

/**
 * @file KwPlaylistNode.h
 * @brief A node on a playlist tree.
 * @author James Hogan <james@albanarts.com>
 */

#include <QVariant>

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

    /// Default constructor.
    KwPlaylistNode();

    /// Destructor.
    virtual ~KwPlaylistNode();

    /*
     * Main interface
     */

    /// Get the parent.
    KwPlaylistNode* getParent();

    /// Get data associated with the node.
    virtual QVariant getData(int role, int column);

    /// Get the number of children.
    virtual int getChildCount() const;

    /// Get a child node by index.
    virtual KwPlaylistNode* getChild(int index);

  private:

    /*
     * Variables
     */

    /// Parent node.
    KwPlaylistNode* m_parent;
};

#endif // _KwPlaylistNode_h_

