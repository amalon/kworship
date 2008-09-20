/**
 * @file KwMediaManager.cpp
 * @brief Media management interface.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwMediaManager.h"
#include "KwMediaPreferencesSequence.h"
#include "KwMediaPreferencesAudio.h"
#include "KwMediaPreferencesVisual.h"

#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <phonon/videowidget.h>

#include <cassert>

/*
 * Constructors + destructors
 */

/// Default constructor.
KwMediaManager::KwMediaManager()
: m_audio()
, m_video()
{
}

/// Destructor.
KwMediaManager::~KwMediaManager()
{
  stopAll();
}

/*
 * Output linking
 */

/// Link the audio to an audio output.
void KwMediaManager::linkAudio(KwAudioOutput* audioOut)
{
  Phonon::Path path;
  if (isAudio())
  {
    path = Phonon::createPath(m_audio.object, audioOut);
    assert(path.isValid());
    connectAudioOutput(audioOut);
  }
  m_audio.outputs.insert(audioOut, path);
}

/// Unlink an audio output.
void KwMediaManager::unlinkAudio(KwAudioOutput* audioOut)
{
  NowPlayingDataAudio::Outputs::iterator it = m_audio.outputs.find(audioOut);
  if (isAudio())
  {
    assert((*it).isValid());
    (*it).disconnect();
    disconnectAudioOutput(audioOut);
  }
  m_audio.outputs.erase(it);
}

/// Link the video to a video output.
void KwMediaManager::linkVideo(KwVideoWidget* videoOut)
{
  Phonon::Path path;
  if (isVideo())
  {
    path = Phonon::createPath(m_video.object, videoOut);
    assert(path.isValid());
    connectVideoOutput(videoOut);
  }
  m_video.outputs.insert(videoOut, path);
}

/// Unlink a video output.
void KwMediaManager::unlinkVideo(KwVideoWidget* videoOut)
{
  NowPlayingDataVideo::Outputs::iterator it = m_video.outputs.find(videoOut);
  if (isVideo())
  {
    assert((*it).isValid());
    (*it).disconnect();
    disconnectVideoOutput(videoOut);
  }
  m_video.outputs.erase(it);
}

/*
 * Starter methods
 */

/// Set up some audio.
KwMediaObject* KwMediaManager::setupAudio(const QUrl& url, KwMediaPreferencesSequence* prefsSequence, KwMediaPreferencesAudio* prefsAudio)
{
  assert(prefsSequence != 0);
  assert(prefsAudio != 0);

  KwMediaObject* mediaObject = new KwMediaObject;
  mediaObject->setCurrentSource(url);

  stopAudio(false);
  m_audio.object = mediaObject;
  m_audio.prefsSequence = prefsSequence;
  m_audio.prefs = prefsAudio;

  prefsSequence->setManager(this);
  prefsAudio->setManager(this);

  // Link media object to audio outputs
  NowPlayingDataAudio::Outputs::iterator it;
  for (it = m_audio.outputs.begin(); it != m_audio.outputs.end(); ++it)
  {
    *it = Phonon::createPath(mediaObject, it.key());
    assert((*it).isValid());
    connectAudioOutput(it.key());
  }

  connectAudioObject();

  audioAdded(false);

  return mediaObject;
}

/// Set up some video.
KwMediaObject* KwMediaManager::setupVideo(const QUrl& url, KwMediaPreferencesSequence* prefsSequence, KwMediaPreferencesVisual* prefsVideo, KwMediaPreferencesAudio* prefsAudio)
{
  assert(prefsSequence != 0);
  assert(prefsVideo != 0);

  // Stop audio iff new video has audio
  stopVideo(prefsAudio != 0);

  KwMediaObject* mediaObject = new KwMediaObject;
  mediaObject->setCurrentSource(url);
  m_video.object = mediaObject;
  m_video.prefsSequence = prefsSequence;
  m_video.prefs = prefsVideo;

  prefsSequence->setManager(this);
  prefsVideo->setManager(this);

  // Link media object to video widgets
  NowPlayingDataVideo::Outputs::iterator it;
  for (it = m_video.outputs.begin(); it != m_video.outputs.end(); ++it)
  {
    *it = Phonon::createPath(mediaObject, it.key());
    assert((*it).isValid());
    connectVideoOutput(it.key());
  }

  connectVideoObject();

  // Keep audio playing if we don't want audio from this video
  if (prefsAudio != 0)
  {
    stopAudio(false);
    m_audio.object = mediaObject;
    m_audio.prefsSequence = prefsSequence;
    m_audio.prefs = prefsAudio;

    prefsAudio->setManager(this);

    // Link media object to audio outputs
    NowPlayingDataAudio::Outputs::iterator it;
    for (it = m_audio.outputs.begin(); it != m_audio.outputs.end(); ++it)
    {
      *it = Phonon::createPath(mediaObject, it.key());
      assert((*it).isValid());
      connectAudioOutput(it.key());
    }

    connectAudioObject();
    audioAdded(true);
  }
  videoAdded(prefsAudio != 0);

  return mediaObject;
}

/*
 * Stopper methods
 */

/// Stop all playing media.
void KwMediaManager::stopAll()
{
  stopAudio();
  stopVideo();
}

/// Stop any playing audio.
void KwMediaManager::stopAudio(bool stopLinkedVideo)
{
  if (isAudio())
  {
    disconnectAudioObject();
    bool linked = isLinked();
    audioRemoved(linked && stopLinkedVideo);
    if (!linked)
    {
      delete m_audio.object;
    }
    else if (!stopLinkedVideo)
    {
      // If we're not deleting object and it remains in use, unlink audio
      NowPlayingDataAudio::Outputs::iterator it;
      for (it = m_audio.outputs.begin(); it != m_audio.outputs.end(); ++it)
      {
        assert((*it).isValid());
        (*it).disconnect();
        disconnectAudioOutput(it.key());
      }
    }
    m_audio.object = 0;
    m_audio.prefsSequence->setManager(0);
    m_audio.prefsSequence = 0;
    m_audio.prefs->setManager(0);
    m_audio.prefs = 0;
    if (linked && stopLinkedVideo)
    {
      stopVideo(false);
    }
  }
}

/// Stop any playing video.
void KwMediaManager::stopVideo(bool stopLinkedAudio)
{
  if (isVideo())
  {
    disconnectVideoObject();
    bool linked = isLinked();
    videoRemoved(linked && stopLinkedAudio);
    if (!linked)
    {
      delete m_video.object;
    }
    else if (!stopLinkedAudio)
    {
      // If we're not deleting object and it remains in use, unlink audio
      NowPlayingDataVideo::Outputs::iterator it;
      for (it = m_video.outputs.begin(); it != m_video.outputs.end(); ++it)
      {
        assert((*it).isValid());
        bool disconnected = (*it).disconnect();
        assert(disconnected);
        disconnectVideoOutput(it.key());
      }
    }
    m_video.object = 0;
    m_video.prefsSequence->setManager(0);
    m_video.prefsSequence = 0;
    m_video.prefs->setManager(0);
    m_video.prefs = 0;
    if (linked && stopLinkedAudio)
    {
      stopAudio(false);
    }
  }
}

/*
 * Accessors
 */

/// Get the audio object.
KwMediaObject* KwMediaManager::getAudioObject()
{
  return m_audio.object;
}

/// Get the video object.
KwMediaObject* KwMediaManager::getVideoObject()
{
  return m_video.object;
}

/// Is linked?
bool KwMediaManager::isLinked() const
{
  return m_audio.object != 0 && m_audio.object == m_video.object;
}

/// Is audio playing?
bool KwMediaManager::isAudio() const
{
  return m_audio.object != 0;
}

/// Is video playing?
bool KwMediaManager::isVideo() const
{
  return m_video.object != 0;
}

/*
 * Media control slots
 */

/// Play/pause audio.
void KwMediaManager::audioPlayPause()
{
  if (isAudio())
  {
    switch (m_audio.object->state())
    {
      case Phonon::PlayingState:
      case Phonon::BufferingState:
        m_audio.object->pause();
        break;

      case Phonon::StoppedState:
      case Phonon::PausedState:
        m_audio.object->play();
        break;

      default:
        break;
    }
  }
}

/// Play/pause video.
void KwMediaManager::videoPlayPause()
{
  if (isVideo())
  {
    switch (m_video.object->state())
    {
      case Phonon::PlayingState:
      case Phonon::BufferingState:
        m_video.object->pause();
        break;

      case Phonon::StoppedState:
      case Phonon::PausedState:
        m_video.object->play();
        break;

      default:
        break;
    }
  }
}

/// Stop audio.
void KwMediaManager::audioStop()
{
  if (isAudio())
  {
    m_audio.object->stop();
  }
}

/// Stop video.
void KwMediaManager::videoStop()
{
  if (isVideo())
  {
    m_video.object->stop();
  }
}

/*
 * Private slots
 */

/// The audio object's metadata has changed.
void KwMediaManager::audioMetaDataHasChanged()
{
  assert(isAudio());

  QStringList title = m_audio.object->metaData("TITLE");
  if (!title.empty())
  {
    audioMediaNameChanged(title.first());
  }
  else
  {
    audioMediaNameChanged("");
  }
}

/// The video object's metadata has changed.
void KwMediaManager::videoMetaDataHasChanged()
{
  assert(isVideo());

  QStringList title = m_video.object->metaData("TITLE");
  if (!title.empty())
  {
    videoMediaNameChanged(title.first());
  }
  else
  {
    videoMediaNameChanged("");
  }
}

/*
 * Internal functions
 */

/// Make the internal connections for a new media object.
void KwMediaManager::connectAudioObject()
{
  // Sequence
  assert(m_audio.object != 0);
  connect(m_audio.object, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SIGNAL(audioStateChanged(Phonon::State,Phonon::State)));
  connect(m_audio.object, SIGNAL(metaDataChanged()), this, SLOT(audioMetaDataHasChanged()));
  // Audio
  assert(m_audio.prefs != 0);
  connect(this, SIGNAL(setVolume(qreal)), m_audio.prefs, SLOT(setVolume(qreal)));
  connect(this, SIGNAL(setMuted(bool)), m_audio.prefs, SLOT(setMuted(bool)));
  connect(this, SIGNAL(setFadeoutMsec(qint32)), m_audio.prefs, SLOT(setFadeoutMsec(qint32)));
  connect(m_audio.prefs, SIGNAL(volumeChanged(qreal)), this, SIGNAL(volumeChanged(qreal)));
  connect(m_audio.prefs, SIGNAL(mutedChanged(bool)), this, SIGNAL(mutedChanged(bool)));

  volumeChanged(m_audio.prefs->getVolume());
  mutedChanged(m_audio.prefs->getMuted());
}

/// Remove the internal connections for an old media object.
void KwMediaManager::disconnectAudioObject()
{
  // Sequence
  assert(m_audio.object != 0);
  disconnect(m_audio.object, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SIGNAL(audioStateChanged(Phonon::State,Phonon::State)));
  disconnect(m_audio.object, SIGNAL(metaDataChanged()), this, SLOT(audioMetaDataHasChanged()));
  // Audio
  assert(m_audio.prefs != 0);
  disconnect(this, SIGNAL(setVolume(qreal)), m_audio.prefs, SLOT(setVolume(qreal)));
  disconnect(this, SIGNAL(setMuted(bool)), m_audio.prefs, SLOT(setMuted(bool)));
  disconnect(this, SIGNAL(setFadeoutMsec(qint32)), m_audio.prefs, SLOT(setFadeoutMsec(qint32)));
  disconnect(m_audio.prefs, SIGNAL(volumeChanged(qreal)), this, SIGNAL(volumeChanged(qreal)));
  disconnect(m_audio.prefs, SIGNAL(mutedChanged(bool)), this, SIGNAL(mutedChanged(bool)));
}

/// Make the internal connections for a new video object.
void KwMediaManager::connectVideoObject()
{
  connect(m_video.object, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SIGNAL(videoStateChanged(Phonon::State,Phonon::State)));
  connect(m_video.object, SIGNAL(metaDataChanged()), this, SLOT(videoMetaDataHasChanged()));
}

/// Remove the internal connections for an old video object.
void KwMediaManager::disconnectVideoObject()
{
  disconnect(m_video.object, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SIGNAL(videoStateChanged(Phonon::State,Phonon::State)));
  disconnect(m_video.object, SIGNAL(metaDataChanged()), this, SLOT(videoMetaDataHasChanged()));
}

/// Make the internal connections for a new audio ouptut.
void KwMediaManager::connectAudioOutput(KwAudioOutput* output)
{
  assert(m_audio.prefs != 0);
  connect(m_audio.prefs, SIGNAL(volumeChanged(qreal)), output, SLOT(setVolume(qreal)));
  connect(m_audio.prefs, SIGNAL(mutedChanged(bool)), output, SLOT(setMuted(bool)));
}

/// Remove the internal connections for an old audio output.
void KwMediaManager::disconnectAudioOutput(KwAudioOutput* output)
{
  assert(m_audio.prefs != 0);
  disconnect(m_audio.prefs, SIGNAL(volumeChanged(qreal)), output, SLOT(setVolume(qreal)));
  disconnect(m_audio.prefs, SIGNAL(mutedChanged(bool)), output, SLOT(setMuted(bool)));
}

/// Make the internal connections for a new video ouptut.
void KwMediaManager::connectVideoOutput(KwVideoWidget* output)
{
  Q_UNUSED(output);
  assert(isVideo());
}

/// Remove the internal connections for an old video output.
void KwMediaManager::disconnectVideoOutput(KwVideoWidget* output)
{
  Q_UNUSED(output);
  assert(isVideo());
}

