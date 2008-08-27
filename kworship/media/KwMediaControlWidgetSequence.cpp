/**
 * @file KwMediaControlWidgetSequence.cpp
 * @brief Controls sequence of playing media items.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwMediaControlWidgetSequence.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

/*
 * Constructors + destructors
 */

/// Primary constructor.
KwMediaControlWidgetSequence::KwMediaControlWidgetSequence(KwMediaManager* manager, QWidget* parent)
: QWidget(parent)
, m_manager(manager)
, m_btnPlayPause(0)
, m_btnStop(0)
, m_lblTitle(0)
{
  QHBoxLayout* layout = new QHBoxLayout;
  layout->setContentsMargins(0, 0, 0, 0);
  setLayout(layout);

  m_btnPlayPause = new QPushButton("Pause", this);
  m_btnPlayPause->setEnabled(false);
  connect(m_btnPlayPause, SIGNAL(clicked()), this, SIGNAL(playPause()));
  layout->addWidget(m_btnPlayPause);

  m_btnStop = new QPushButton("Stop", this);
  m_btnStop->setEnabled(false);
  connect(m_btnStop, SIGNAL(clicked()), this, SIGNAL(stop()));
  layout->addWidget(m_btnStop);

  m_lblTitle = new QLabel("", this);
  layout->addWidget(m_lblTitle);

}

/// Destructor.
KwMediaControlWidgetSequence::~KwMediaControlWidgetSequence()
{
}

/*
 * Slots
 */

/// Change the state of the media.
void KwMediaControlWidgetSequence::changeState(Phonon::State newState, Phonon::State oldState)
{
  Q_UNUSED(oldState)
  m_btnStop->setEnabled(newState != Phonon::StoppedState);
  switch (newState)
  {
    case Phonon::PlayingState:
    case Phonon::BufferingState:
      m_btnPlayPause->setText("Pause");
      m_btnPlayPause->setEnabled(true);
      break;

    case Phonon::StoppedState:
    case Phonon::PausedState:
      m_btnPlayPause->setText("Play");
      m_btnPlayPause->setEnabled(true);
      break;

    default:
      m_btnPlayPause->setText("Play");
      m_btnPlayPause->setEnabled(false);
      break;
  }
}

/// Set the name of the media.
void KwMediaControlWidgetSequence::setMediaName(QString name)
{
  m_lblTitle->setText(name);
}

