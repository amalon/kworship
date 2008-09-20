#ifndef _KwSongdbLyrics_h_
#define _KwSongdbLyrics_h_

/**
 * @file KwSongdbLyrics.h
 * @brief A verse of lyrics from the database.
 * @author James Hogan <james@albanarts.com>
 */

#include <QString>

/// A verse of lyrics from the database.
class KwSongdbLyrics
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwSongdbLyrics(int id, const QString& lyrics);

    /// Destructor.
    virtual ~KwSongdbLyrics();

    /*
     * Accessors
     */

    /// Get lyrics id.
    int getId() const;

    /// Get the lyrics.
    QString getLyrics() const;

  private:

    /*
     * Variables
     */

    /// Lyrics id.
    int m_id;

    /// Actual lyrics.
    QString m_lyrics;
};

#endif // _KwSongdbLyrics_h_

