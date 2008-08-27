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

  // Create all the widgets invisible to start off with.
  m_audioSequencer = new KwMediaControlWidgetSequence(manager, this);
  m_audioSequencer->setVisible(false);
  layout->addWidget(m_audioSequencer);
  connect(m_audioSequencer, SIGNAL(playPause()), manager, SLOT(audioPlayPause()));
  connect(m_audioSequencer, SIGNAL(stop()), manager, SLOT(audioStop()));
  connect(manager, SIGNAL(audioStateChanged(Phonon::State,Phonon::State)), m_audioSequencer, SLOT(changeState(Phonon::State,Phonon::State)));
  connect(manager, SIGNAL(audioMediaNameChanged(QString)), m_audioSequencer, SLOT(setMediaName(QString)));

  m_videoSequencer = new KwMediaControlWidgetSequence(manager, this);
  m_videoSequencer->setVisible(false);
  layout->addWidget(m_videoSequencer);
  connect(m_videoSequencer, SIGNAL(playPause()), manager, SLOT(videoPlayPause()));
  connect(m_videoSequencer, SIGNAL(stop()), manager, SLOT(videoStop()));
  connect(manager, SIGNAL(videoStateChanged(Phonon::State,Phonon::State)), m_videoSequencer, SLOT(changeState(Phonon::State,Phonon::State)));
  connect(manager, SIGNAL(videoMediaNameChanged(QString)), m_videoSequencer, SLOT(setMediaName(QString)));

  m_audio = new KwMediaControlWidgetAudio(manager, this);
  m_audio->setVisible(false);
  connect(m_audio, SIGNAL(mutedChanged(bool)), manager, SIGNAL(setMuted(bool)));
  connect(m_audio, SIGNAL(volumeChanged(qreal)), manager, SIGNAL(setVolume(qreal)));
  connect(manager, SIGNAL(volumeChanged(qreal)), m_audio, SLOT(setVolume(qreal)));
  layout->addWidget(m_audio);

  m_visual = new KwMediaControlWidgetVisual(manager, this);
  m_visual->setVisible(false);
  layout->addWidget(m_visual);

  // Connect to media manager.
  connect(manager, SIGNAL(audioAdded(bool)), this, SLOT(addAudio(bool)));
  connect(manager, SIGNAL(videoAdded(bool)), this, SLOT(addVideo(bool)));
  connect(manager, SIGNAL(audioRemoved(bool)), this, SLOT(removeAudio(bool)));
  connect(manager, SIGNAL(videoRemoved(bool)), this, SLOT(removeVideo(bool)));
}

/// Destructor.
KwMediaControlWidget::~KwMediaControlWidget()
{
}

/*
 * Slots
 */

/// Audio has been added.
void KwMediaControlWidget::addAudio(bool linkedVideo)
{
  m_audio->setVisible(true);
  if (!linkedVideo)
  {
    m_audioSequencer->setVisible(true);
  }
}

/// Video has been added.
void KwMediaControlWidget::addVideo(bool linkedAudio)
{
  Q_UNUSED(linkedAudio);
  m_visual->setVisible(true);
  m_videoSequencer->setVisible(true);
}

/// Audio has been removed.
void KwMediaControlWidget::removeAudio(bool removeLinkedVideo)
{
  Q_UNUSED(removeLinkedVideo);
  m_audio->setVisible(false);
  m_audioSequencer->setVisible(false);
}

/// Video has been removed.
void KwMediaControlWidget::removeVideo(bool removeLinkedAudio)
{
  Q_UNUSED(removeLinkedAudio);
  m_visual->setVisible(false);
  if (m_audio->isVisible())
  {
    m_audioSequencer->setVisible(true);
  }
  m_videoSequencer->setVisible(false);
}

