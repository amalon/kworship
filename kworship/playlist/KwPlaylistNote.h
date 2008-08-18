#ifndef _KwPlaylistNote_h_
#define _KwPlaylistNote_h_

/**
 * @file KwPlaylistNote.h
 * @brief A plain text playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistItem.h"

#include <QString>

/// A plain text playlist item.
class KwPlaylistNote : public KwPlaylistItem
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistNote(QString content);

    /// Destructor.
    virtual ~KwPlaylistNote();

    /*
     * Main interface.
     */

    /// Get the text.
    QString getContent() const;

    virtual KwPlaylistNode* getNode();

  private:

    /*
     * Variables
     */

    /// Text in the note.
    QString m_content;
};

#endif // _KwPlaylistNote_h_

