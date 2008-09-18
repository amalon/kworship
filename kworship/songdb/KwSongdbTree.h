#ifndef _KwSongdbTree_h_
#define _KwSongdbTree_h_

/**
 * @file KwSongdbTree.h
 * @brief A tree widget with songs from songdb.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbFilter.h"

#include <QTreeView>

class KwSongdbModel;
class QActionGroup;

/// A tree widget with songs from songdb.
class KwSongdbTree : public QTreeView
{
  Q_OBJECT
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwSongdbTree(QWidget* parent = 0);

    /// Destructor.
    virtual ~KwSongdbTree();

    /*
     * Actions
     */

    /// Get the group by actions.
    QActionGroup* groupByActions();

  private slots:

    /*
     * Private slots
     */

    /// Activate a grouping.
    void groupBy(const KwSongdbFilterLevelList* filters);


  private:

    /*
     * Variables
     */

    /// Model.
    KwSongdbModel* m_model;

    /// Group by actions.
    QActionGroup* m_groupByActions;

    /// 
};

#endif // _KwSongdbTree_h_

