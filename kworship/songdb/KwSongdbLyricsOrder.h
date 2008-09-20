#ifndef _KwSongdbLyricsOrder_h_
#define _KwSongdbLyricsOrder_h_

/**
 * @file KwSongdbLyricsOrder.h
 * @brief An order item for a song from the database.
 * @author James Hogan <james@albanarts.com>
 */

class KwSongdbLyrics;

/// An order item for a song from the database.
class KwSongdbLyricsOrder
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwSongdbLyricsOrder(int order, KwSongdbLyrics* lyrics);

    /// Destructor.
    virtual ~KwSongdbLyricsOrder();

    /*
     * Accessors
     */

    /// Get the order.
    int getOrder() const;

    /// Get the lyrics object.
    KwSongdbLyrics* getLyrics() const;

  private:

    /*
     * Variables
     */

    /// Lyrics order.
    int m_order;

    /// Lyrics object.
    KwSongdbLyrics* m_lyrics;
};

#endif // _KwSongdbLyricsOrder_h_

