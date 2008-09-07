#ifndef _KwPlaylistSong_h_
#define _KwPlaylistSong_h_

/**
 * @file KwPlaylistSong.h
 * @brief A plain text playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistPaged.h"

/// A plain text playlist item.
class KwPlaylistSong : public KwPlaylistPaged
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Default constructor.
    KwPlaylistSong(const QString& label, const QStringList& blocks);

    /// Destructor.
    virtual ~KwPlaylistSong();

    /*
     * Main interface
     */

    /// Get the label.
    QString getLabel() const;

    virtual KwPlaylistNode* getNode(KwPlaylistNode* parent);

  private:
    
    /*
     * Variables
     */

    /// Label.
    QString m_label;
};

#endif // _KwPlaylistSong_h_

