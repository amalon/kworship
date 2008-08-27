/**
 * @file KwMediaItem.cpp
 * @brief A media item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwMediaItem.h"
#include "KwMediaManager.h"
#include "KwMediaPreferencesSequence.h"
#include "KwMediaPreferencesAudio.h"
#include "KwMediaPreferencesVisual.h"

#include <phonon/mediaobject.h>

/*
 * Constructors + destructors
 */

/// Default constructor.
KwMediaItem::KwMediaItem(QString url)
: m_url(url)
, m_sequencePreferences(0)
, m_audioPreferences(0)
, m_visualPreferences(0)
{
}

/// Destructor.
KwMediaItem::~KwMediaItem()
{
  delete m_sequencePreferences;
  delete m_audioPreferences;
  delete m_visualPreferences;
}

/*
 * Main interface
 */

/// Start playing the media through a media manager.
void KwMediaItem::playMedia(KwMediaManager* mediaManager)
{
  // Sequence must be enabled
  if (0 != m_sequencePreferences)
  {
    if (0 != m_visualPreferences)
    {
      // The media has video
      mediaManager->setupVideo(m_url, m_sequencePreferences, m_visualPreferences, m_audioPreferences); //->play();
    }
    else if (0 != m_audioPreferences)
    {
      // The media has audio
      mediaManager->setupAudio(m_url, m_sequencePreferences, m_audioPreferences); //->play();
    }
  }
}

/// Enable sequence.
void KwMediaItem::setSequence(bool enabled)
{
  if (enabled)
  {
    if (0 == m_sequencePreferences)
    {
      m_sequencePreferences = new KwMediaPreferencesSequence();
    }
  }
  else
  {
    delete m_sequencePreferences;
    m_sequencePreferences = 0;
  }
}

/// Enable audio.
void KwMediaItem::setAudio(bool enabled)
{
  setSequence(enabled);
  if (enabled)
  {
    if (0 == m_audioPreferences)
    {
      m_audioPreferences = new KwMediaPreferencesAudio();
    }
  }
  else
  {
    delete m_audioPreferences;
    m_audioPreferences = 0;
  }
}

/// Enable video.
void KwMediaItem::setVideo(bool enabled)
{
  setSequence(enabled);
  if (enabled)
  {
    if (0 == m_visualPreferences)
    {
      m_visualPreferences = new KwMediaPreferencesVisual();
    }
  }
  else
  {
    delete m_visualPreferences;
    m_visualPreferences = 0;
  }
}

/*
 * Accessors
 */

/// Get the url of the file.
QString KwMediaItem::getUrl() const
{
  return m_url;
}

