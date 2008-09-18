#ifndef _KwSongdbFilterNode_h_
#define _KwSongdbFilterNode_h_

/**
 * @file KwSongdbFilterNode.h
 * @brief A node for filtering songs.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbNode.h"
#include "KwSongdbFilter.h"

#include <QString>

class QSqlQuery;

/// A node for filtering songs.
class KwSongdbFilterNode : public KwSongdbNode
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwSongdbFilterNode(const KwSongdbFilterLevelList* filters, QString label, KwSongdbNode* parent);

    /// Destructor.
    virtual ~KwSongdbFilterNode();

    /*
     * Main interface
     */

    /// Get data associated with the node.
    virtual QVariant getData(int role, int column);

    /// Get the number of children.
    virtual int getChildCount() const;

  protected:

    /// Get a child node by index.
    virtual KwSongdbNode* _getChild(int index);

    /// Get a new node of this type.
    KwSongdbFilterNode* _newNode(QString label, QString idExpression, int idValue);

    /// Get a new final node.
    KwSongdbNode* _newFinalNode(QString label, int id);

  private:

    /*
     * Types
     */

    /// A known value from a previous filter.
    struct KnownValue
    {
      QString idExpression;
      int idValue;
      KnownValue* next;
    };

    /*
     * Variables
     */

    /// Label.
    QString m_label;

    /// The shared list of filters.
    const KwSongdbFilterLevelList* m_filterLevels;

    /// The current filter level we're on.
    int m_currentFilter;

    /// The list of known values.
    KnownValue m_knownValue;

    /// Current SQL query.
    QSqlQuery* m_query;

    /*
     * Private constructors
     */

    /// Primary constructor.
    KwSongdbFilterNode(KwSongdbFilterNode* parent, QString label, QString knownIdExpression, int knownId);

    /*
     * Private functions
     */

    /// Setup the query.
    void setupQuery();
};

#endif // _KwSongdbFilterNode_h_

