#ifndef _KwCssStyleSheetFile_h_
#define _KwCssStyleSheetFile_h_

/**
 * @file KwCssStyleSheetFile.h
 * @brief File backed cascading style sheet.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssStyleSheet.h"

#include <QString>

/// File backed cascading style sheet.
class KwCssStyleSheetFile : public KwCssStyleSheet
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwCssStyleSheetFile(QString path);

    /// Destructor.
    virtual ~KwCssStyleSheetFile();

    /*
     * Main interface.
     */

    /// Load the file.
    void load();

    /// Save the file.
    void save() const;

  private:

    /*
     * Variables
     */

    /// Path to file.
    QString m_path;
};

#endif // _KwCssStyleSheetFile_h_

