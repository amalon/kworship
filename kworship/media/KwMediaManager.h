#ifndef _KwMediaManager_h_
#define _KwMediaManager_h_

/**
 * @file KwMediaManager.h
 * @brief Manage currently playing media.
 * @author James Hogan <james@albanarts.com>
 */

#include <phonon/path.h>

#include <phonon/phononnamespace.h>

#include <QObject>
#include <QUrl>
#include <QSet>

namespace Phonon
{
  class AudioOutput;
  class MediaObject;
  class MediaSource;
  class VideoWidget;
}

class KwMediaPreferencesSequence;
class KwMediaPreferencesAudio;
class KwMediaPreferencesVisual;

/*
 * Just in case we want to add some more management code in.
 */

typedef Phonon::AudioOutput KwAudioOutput;
typedef Phonon::MediaObject KwMediaObject;
typedef Phonon::MediaObject KwMediaSource;
typedef Phonon::VideoWidget KwVideoWidget;

/// Manage currently playing media.
class KwMediaManager : public QObject
{
    Q_OBJECT
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwMediaManager();

    /// Destructor.
    virtual ~KwMediaManager();

    /*
     * Output linking
     */

    /// Link the audio to an audio output.
    void linkAudio(KwAudioOutput* audioOut);

    /// Unlink an audio output.
    void unlinkAudio(KwAudioOutput* audioOut);

    /// Link the video to a video output.
    void linkVideo(KwVideoWidget* videoOut);

    /// Unlink a video output.
    void unlinkVideo(KwVideoWidget* videoOut);

    /*
     * Starter methods
     */

    /// Set up some audio.
    /**
     * Sets audio playing with certain preferences.
     * The preferences can be altered while playing and will update live where possible.
     * @return The media object which needs attaching to the apropriate outputs.
     */
    KwMediaObject* setupAudio(const QUrl& url, KwMediaPreferencesSequence* prefsSequence, KwMediaPreferencesAudio* prefsAudio);

    /// Set up some video.
    /**
     * Sets video/audio playing with certain preferences.
     * The preferences can be altered while playing and will update live where possible.
     * @return The media object which needs attaching to the apropriate outputs.
     */
    KwMediaObject* setupVideo(const QUrl& url, KwMediaPreferencesSequence* prefsSequence, KwMediaPreferencesVisual* prefsVideo, KwMediaPreferencesAudio* prefsAudio = 0);

    /*
     * Stopper methods
     */

    /// Stop all playing media.
    void stopAll();

    /// Stop any playing audio.
    /**
     * @param stopLinkedVideo Whether to stop linked video also.
     */
    void stopAudio(bool stopLinkedVideo = true);

    /// Stop any playing video.
    /**
     * @param stopLinkedVideo Whether to stop linked audio also.
     */
    void stopVideo(bool stopLinkedVideo = true);

    /*
     * Accessors
     */

    /// Get the audio object.
    KwMediaObject* getAudioObject();

    /// Get the video object.
    KwMediaObject* getVideoObject();

    /// Is linked?
    bool isLinked() const;

    /// Is audio playing?
    bool isAudio() const;

    /// Is video playing?
    bool isVideo() const;

  public slots:

    /*
     * Media control slots
     */

    /// Play/pause audio.
    void audioPlayPause();

    /// Play/pause video.
    void videoPlayPause();

    /// Stop audio.
    void audioStop();

    /// Stop video.
    void videoStop();

  signals:

    /*
     * Sequence signals
     */

    /// Audio has changed.
    void audioAdded(bool videoLinked);
    /// Video has been added.
    void videoAdded(bool audioLinked);

    /// Audio has been removed.
    void audioRemoved(bool linkedVideoRemoved);
    /// Video has been removed.
    void videoRemoved(bool linkedVideoRemoved);

    /// Audio media name changed.
    void audioMediaNameChanged(QString name);
    /// Video media name changed.
    void videoMediaNameChanged(QString name);

    /// Audio has changed state.
    void audioStateChanged(Phonon::State newState, Phonon::State oldState);
    /// Video has changed state.
    void videoStateChanged(Phonon::State newState, Phonon::State oldState);

    /*
     * Audio signals
     */

    /// Set the volume level.
    void setVolume(qreal volume);

    /// Set whether the audio is muted.
    void setMuted(bool muted);

    /// Set the fadeout time in msecs.
    void setFadeoutMsec(qint32 fadeoutMsec);

    /// Volume level has changed.
    void volumeChanged(qreal newVolume);

    /// Muted has changed.
    void mutedChanged(bool muted);

  private slots:

    /*
     * Private slots
     */

    /// The audio object's metadata has changed.
    void audioMetaDataHasChanged();
    /// The video object's metadata has changed.
    void videoMetaDataHasChanged();

  private:

    /*
     * Types
     */

    /// Now playing data for a certain media type (audio/visual).
    template <class PREFS, class OUTPUT>
    class NowPlayingData
    {
      public:

        /*
         * Types
         */

        /// Set of outputs.
        typedef QMap<OUTPUT*, Phonon::Path> Outputs;

        /*
         * Variables
         */

        /// Currently playing media object.
        KwMediaObject* object;

        /// Sequence preferences.
        KwMediaPreferencesSequence* prefsSequence;

        /// Specific preferences.
        PREFS* prefs;

        /// Set of linked outputs.
        Outputs outputs;

        /*
         * Constructor
         */

        /// Default constructor.
        NowPlayingData()
        : object(0)
        , prefsSequence(0)
        , prefs(0)
        , outputs()
        {
        }
    };

    typedef NowPlayingData<KwMediaPreferencesAudio, KwAudioOutput>  NowPlayingDataAudio;
    typedef NowPlayingData<KwMediaPreferencesVisual, KwVideoWidget> NowPlayingDataVideo;

    /*
     * Variables
     */

    /// Now playing audio data.
    NowPlayingDataAudio m_audio;

    /// Now playing video data.
    NowPlayingDataVideo m_video;

    /*
     * Internal functions
     */

    /// Make the internal connections for a new media object.
    void connectAudioObject();
    /// Remove the internal connections for an old media object.
    void disconnectAudioObject();

    /// Make the internal connections for a new video object.
    void connectVideoObject();
    /// Remove the internal connections for an old video object.
    void disconnectVideoObject();

    /// Make the internal connections for a new audio ouptut.
    void connectAudioOutput(KwAudioOutput* output);
    /// Remove the internal connections for an old audio output.
    void disconnectAudioOutput(KwAudioOutput* output);

    /// Make the internal connections for a new video ouptut.
    void connectVideoOutput(KwVideoWidget* output);
    /// Remove the internal connections for an old video output.
    void disconnectVideoOutput(KwVideoWidget* output);


};

#endif // _KwMediaManager_h_

