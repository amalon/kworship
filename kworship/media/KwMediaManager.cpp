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
  }
  m_video.outputs.erase(it);
}

/*
 * Starter methods
 */

/// Set up some audio.
KwMediaObject* KwMediaManager::setupAudio(QString url, KwMediaPreferencesSequence* prefsSequence, KwMediaPreferencesAudio* prefsAudio)
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
  }

  return mediaObject;
}

/// Set up some video.
KwMediaObject* KwMediaManager::setupVideo(QString url, KwMediaPreferencesSequence* prefsSequence, KwMediaPreferencesVisual* prefsVideo, KwMediaPreferencesAudio* prefsAudio)
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
  }

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
    }
  }

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
    bool linked = isLinked();
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
    bool linked = isLinked();
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

