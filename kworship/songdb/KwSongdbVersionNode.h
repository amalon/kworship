#ifndef _KwSongdbVersionNode_h_
#define _KwSongdbVersionNode_h_

/**
 * @file KwSongdbVersionNode.h
 * @brief A node for a song version.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbNode.h"

/// A node for filtering songs.
class KwSongdbVersionNode : public KwSongdbNode
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwSongdbVersionNode(KwSongdbNode* parent, QString label, int id);

    /// Destructor.
    virtual ~KwSongdbVersionNode();

    /*
     * Main interface
     */

    /// Get data associated with the node.
    virtual QVariant getData(int role, int column);

    /// Get flags for this item.
    virtual Qt::ItemFlags getFlags(Qt::ItemFlags defaultFlags) const;

    /// Get mime data string for this set of songs.
    virtual QString mimeData() const;

  private:

    /*
     * Variables
     */

    /// Label.
    QString m_label;

    /// Version id.
    int m_id;
};

#endif // _KwSongdbNode_h_

