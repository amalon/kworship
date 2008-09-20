#ifndef _KwPlaylistFile_h_
#define _KwPlaylistFile_h_

/**
 * @file KwPlaylistFile.h
 * @brief A file based playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistItem.h"

#include <QUrl>

class KwDisplayManager;

/// A file based playlist item.
class KwPlaylistFile : public KwPlaylistItem
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistFile(const QUrl& url);

    /// Destructor.
    virtual ~KwPlaylistFile();

    /*
     * Main interface.
     */

    virtual KwPlaylistNode* getNode(KwPlaylistNode* parent);

    /// Activate the file.
    virtual void activate(KwDisplayManager* manager);

    /*
     * Accessors
     */

    /// Get the image url.
    QUrl getUrl() const;

  private:
    
    /*
     * Variables
     */

    /// File url.
    QUrl m_url;
};

#endif // _KwPlaylistFile_h_

