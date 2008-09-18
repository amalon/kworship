/**
 * @file KwSongdbTreeGroupAction.cpp
 * @brief An action for grouping songs in tree.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbTreeGroupAction.h"
#include "KwSongdbFilter.h"

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwSongdbTreeGroupAction::KwSongdbTreeGroupAction(QString label, KwSongdbFilterLevelList* filters, QObject* parent)
: QAction(label, parent)
, m_filters(filters)
{
  connect(this, SIGNAL(triggered()), this, SLOT(trigger()));
}

/// Destructor.
KwSongdbTreeGroupAction::~KwSongdbTreeGroupAction()
{
  delete m_filters;
}

/*
 * Public slots
 */

/// Trigger new triggered signal.
void KwSongdbTreeGroupAction::trigger()
{
  // Trigger signal
  triggered(m_filters);
}

