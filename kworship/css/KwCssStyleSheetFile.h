/***************************************************************************
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   This file is part of KWorship.                                        *
 *                                                                         *
 *   KWorship is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   KWorship is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with KWorship.  If not, see <http://www.gnu.org/licenses/>.     *
 ***************************************************************************/

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

