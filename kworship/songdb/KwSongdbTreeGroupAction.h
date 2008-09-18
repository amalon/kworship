#ifndef _KwSongdbTreeGroupAction_h_
#define _KwSongdbTreeGroupAction_h_

/**
 * @file KwSongdbTreeGroupAction.h
 * @brief An action for grouping songs in tree.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbFilter.h"

#include <QAction>

/// An action for grouping songs in tree.
class KwSongdbTreeGroupAction : public QAction
{
  Q_OBJECT
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwSongdbTreeGroupAction(QString label, KwSongdbFilterLevelList* filters, QObject* parent = 0);

    /// Destructor.
    virtual ~KwSongdbTreeGroupAction();

  public slots:

    /*
     * Public slots
     */

    /// Trigger new triggered signal.
    void trigger();

  signals:
    
    /*
     * Signals
     */

    /// Action is triggered with a list of filters.
    void triggered(const KwSongdbFilterLevelList* filters);

  private:

    /*
     * Variables
     */

    /// Filter list.
    KwSongdbFilterLevelList* m_filters;

};

#endif // _KwSongdbTreeGroupAction_h_

