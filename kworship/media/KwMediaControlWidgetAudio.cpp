/**
 * @file KwMediaControlWidgetAudio.cpp
 * @brief Controls audio preferences of playing media items.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwMediaControlWidgetAudio.h"

#include <QVBoxLayout>
#include <QCheckBox>
#include <QSlider>

/*
 * Constructors + destructors
 */

/// Primary constructor.
KwMediaControlWidgetAudio::KwMediaControlWidgetAudio(KwMediaManager* manager, QWidget* parent)
: QWidget(parent)
, m_manager(manager)
, m_chkMuted(0)
, m_sliderVolume(0)
{
  QVBoxLayout* layout = new QVBoxLayout;
  layout->setContentsMargins(0, 0, 0, 0);
  setLayout(layout);

  m_chkMuted = new QCheckBox("Mute", this);
  connect(m_chkMuted, SIGNAL(toggled(bool)), this, SIGNAL(mutedChanged(bool)));
  layout->addWidget(m_chkMuted);

  m_sliderVolume = new QSlider(Qt::Horizontal, this);
  m_sliderVolume->setMaximum(100);
  connect(m_sliderVolume, SIGNAL(sliderMoved(int)), this, SLOT(volumeSliderMoved(int)));
  layout->addWidget(m_sliderVolume);
}

/// Destructor.
KwMediaControlWidgetAudio::~KwMediaControlWidgetAudio()
{
}

/*
 * Public slots
 */

/// Set volume.
void KwMediaControlWidgetAudio::setVolume(qreal volume)
{
  m_sliderVolume->setValue((int)(volume*100));
}

/*
 * Private slots
 */

/// The volume slider has moved.
void KwMediaControlWidgetAudio::volumeSliderMoved(int value)
{
  volumeChanged((qreal)value / 100.0);
}

