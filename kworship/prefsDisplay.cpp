#include "prefsDisplay.h"
#include "DesktopView.h"
#include "settings.h"

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
  desktopView->setObjectName("kcfg_displayScreen");
  connect(desktopView, SIGNAL(screenSelected(int, bool)), this, SLOT(screenSelect(int, bool)));
  connect(desktopView, SIGNAL(statusChanged(QString)), labelStatus, SLOT(setText(QString)));
  layoutScreens->addWidget(desktopView);

  connect(kcfg_displayScreenChoose, SIGNAL(toggled(bool)), desktopView, SLOT(setEnabled(bool)));
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

