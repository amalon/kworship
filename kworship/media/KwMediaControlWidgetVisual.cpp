/**
 * @file KwMediaControlWidgetVisual.cpp
 * @brief Controls visual preferences of playing media items.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwMediaControlWidgetVisual.h"

#include <QVBoxLayout>
#include <QSlider>

/*
 * Constructors + destructors
 */

/// Primary constructor.
KwMediaControlWidgetVisual::KwMediaControlWidgetVisual(KwMediaManager* manager, QWidget* parent)
: QWidget(parent)
, m_manager(manager)
{
  QVBoxLayout* layout = new QVBoxLayout;
  layout->setContentsMargins(0, 0, 0, 0);
  setLayout(layout);
}

/// Destructor.
KwMediaControlWidgetVisual::~KwMediaControlWidgetVisual()
{
}

