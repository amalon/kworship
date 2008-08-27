/**
 * @file KwMediaControlWidget.cpp
 * @brief Controls the preferences of the currently playing media items.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwMediaManager.h"
#include "KwMediaControlWidget.h"
#include "KwMediaControlWidgetSequence.h"
#include "KwMediaControlWidgetAudio.h"
#include "KwMediaControlWidgetVisual.h"

#include <QHBoxLayout>

/*
 * Constructors + destructors
 */

/// Primary constructor.
KwMediaControlWidget::KwMediaControlWidget(KwMediaManager* manager, QWidget* parent)
: QWidget(parent)
, m_manager(manager)
, m_audioSequencer(0)
, m_videoSequencer(0)
, m_audio(0)
, m_visual(0)
{
  QHBoxLayout* layout = new QHBoxLayout;
  layout->setContentsMargins(0, 0, 0, 0);
  setLayout(layout);

  m_videoSequencer = new KwMediaControlWidgetSequence(manager, this);
  layout->addWidget(m_videoSequencer);
  connect(m_videoSequencer, SIGNAL(playPause()), manager, SLOT(videoPlayPause()));
  connect(m_videoSequencer, SIGNAL(stop()), manager, SLOT(videoStop()));
  connect(manager, SIGNAL(videoStateChanged(Phonon::State,Phonon::State)), m_videoSequencer, SLOT(changeState(Phonon::State,Phonon::State)));
  connect(manager, SIGNAL(videoMediaNameChanged(QString)), m_videoSequencer, SLOT(setMediaName(QString)));

  m_audio = new KwMediaControlWidgetAudio(manager, this);
  connect(m_audio, SIGNAL(mutedChanged(bool)), manager, SIGNAL(setMuted(bool)));
  connect(m_audio, SIGNAL(volumeChanged(qreal)), manager, SIGNAL(setVolume(qreal)));
  connect(manager, SIGNAL(volumeChanged(qreal)), m_audio, SLOT(setVolume(qreal)));
  layout->addWidget(m_audio);
}

/// Destructor.
KwMediaControlWidget::~KwMediaControlWidget()
{
}

