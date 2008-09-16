#include "prefsDisplay.h"
#include "DesktopView.h"

/**
 * Default constructor
 */
prefsDisplay::prefsDisplay(QWidget *parent)
: QWidget(parent)
, Ui::prefsDisplay_base()
, m_desktopRect()
{
  setupUi(this);

  DesktopView* desktopView = new DesktopView(this);
  connect(desktopView, SIGNAL(screenSelected(int, bool)), this, SLOT(screenSelect(int, bool)));
  connect(desktopView, SIGNAL(statusChanged(QString)), labelStatus, SLOT(setText(QString)));
  layoutScreens->addWidget(desktopView);

  connect(radioChoose, SIGNAL(toggled(bool)), desktopView, SLOT(setEnabled(bool)));
  desktopView->setEnabled(radioChoose->isDown());
}

/**
 * Destructor
 */
prefsDisplay::~prefsDisplay()
{
}

/// Indicates that a screen selection has changed.
void prefsDisplay::screenSelect(int screen, bool selected)
{
  Q_UNUSED(screen)
  Q_UNUSED(selected)
}

