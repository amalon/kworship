#ifndef _KwPlaylistText_h_
#define _KwPlaylistText_h_

/**
 * @file KwPlaylistText.h
 * @brief A plain text playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistPaged.h"

/// A plain text playlist item.
class KwPlaylistText : public KwPlaylistPaged
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Default constructor.
    KwPlaylistText(const QString& label, const QStringList& blocks);

    /// Destructor.
    virtual ~KwPlaylistText();

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

#endif // _KwPlaylistText_h_

