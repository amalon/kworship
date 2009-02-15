/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   KWorship is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   KWorship is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with KWorship.  If not, write to the Free Software Foundation,  *
 *   Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.   *
 ***************************************************************************/

#ifndef _KwExportFilter_h_
#define _KwExportFilter_h_

/**
 * @file KwExportFilter.h
 * @brief Export file filter.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwFilter.h"

#include <kdemacros.h>

#include <QStringList>
#include <QString>
#include <QList>

class KwDocument;
class KUrl;

/// Export file filter.
class KDE_EXPORT KwExportFilter : public virtual KwFilter
{
  public:

    /*
     * Types
     */

    /// Abstract description of something that cannot be saved.
    class Limitation
    {
      public:

        /*
         * Constructors + destructor
         */

        /// Default constructor.
        Limitation();

        /// Destructor.
        virtual ~Limitation();

        /*
         * Main interface
         */

        /// Get a short description of what won't be saved
        virtual QString briefDescription() = 0;

        /// Get a detailed description of what won't be saved
        virtual QString detailedDescription() = 0;
    };

    /// Container class of limitations.
    class Limitations
    {
      public:

        /*
         * Constructors + destructor
         */

        /// Default constructor.
        Limitations();

        /// Destructor.
        virtual ~Limitations();

      private:

        /*
         * Variables
         */

        /// List of limitations.
        QList<Limitation*> m_limitations;
    };

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwExportFilter();

    /// Destructor.
    virtual ~KwExportFilter();

    /*
     * Main interface
     */

    /// Obtain information about any data that can not be saved.
    void saveLimitations(KwDocument* doc, const QString& mimeType, Limitations* o_limitations);

    /// Save the document to file.
    virtual bool save(KwDocument* doc, const KUrl& url, const QString& mimeType) = 0;

    /*
     * Accessors
     */

    /// Get a list of export mime types.
    QStringList exportMimeTypes() const;
    
  protected:

    /*
     * Virtual interface
     */

    /// Obtain information about any data that can not be saved.
    virtual void v_saveLimitations(KwDocument* doc, const QString& mimeType, Limitations* o_limitations) = 0;

    /*
     * Variables
     */

    /// List of export mime types.
    QStringList m_exportMimeTypes;
};

#endif // _KwExportFilter_h_
