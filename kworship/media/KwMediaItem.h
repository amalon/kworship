#ifndef _KwMediaItem_h_
#define _KwMediaItem_h_

/**
 * @file KwMediaItem.h
 * @brief A media item.
 * @author James Hogan <james@albanarts.com>
 */

#include <QString>

class KwMediaManager;
class KwMediaPreferencesSequence;
class KwMediaPreferencesAudio;
class KwMediaPreferencesVisual;

/// A media item.
class KwMediaItem
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwMediaItem(QString url);

    /// Destructor.
    virtual ~KwMediaItem();

    /*
     * Main interface
     */

    /// Start playing the media through a media manager.
    void playMedia(KwMediaManager* mediaManager);

    /// Enable sequence.
    void setSequence(bool enabled);

    /// Enable audio.
    void setAudio(bool enabled);

    /// Enable video.
    void setVideo(bool enabled);

    /*
     * Accessors
     */

    /// Get the url of the file.
    QString getUrl() const;

  private:

    /*
     * Variables
     */

    /// Url.
    QString m_url;

    /// Sequence preferences.
    KwMediaPreferencesSequence* m_sequencePreferences;

    /// Audio preferences.
    KwMediaPreferencesAudio* m_audioPreferences;

    /// Visual preferences.
    KwMediaPreferencesVisual* m_visualPreferences;
};

#endif // _KwMediaItem_h_

