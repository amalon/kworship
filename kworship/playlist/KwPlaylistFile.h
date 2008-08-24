#ifndef _KwPlaylistFile_h_
#define _KwPlaylistFile_h_

/**
 * @file KwPlaylistFile.h
 * @brief A file based playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistItem.h"

#include <QString>

class KwDisplayManager;

/// A file based playlist item.
class KwPlaylistFile : public KwPlaylistItem
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    KwPlaylistFile(QString url);

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
    QString getUrl() const;

  private:
    
    /*
     * Variables
     */

    /// File url.
    QString m_url;
};

#endif // _KwPlaylistFile_h_

