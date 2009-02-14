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

#ifndef _KwFilterManager_h_
#define _KwFilterManager_h_

/**
 * @file KwFilterManager.h
 * @brief Manages file filters.
 * @author James Hogan <james@albanarts.com>
 */

#include <kdemacros.h>

#include <QList>
#include <QHash>
#include <QStringList>

class KwImportFilter;
class KwExportFilter;
class KwLoadSaveFilter;

/// Manages file filter.
class KDE_EXPORT KwFilterManager
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwFilterManager();

    /// Destructor.
    virtual ~KwFilterManager();

    /*
     * Main interface
     */

    /// Add a load save filter.
    void addLoadSaveFilter(KwLoadSaveFilter* loadSaveFilter, bool makeDefault = false);

    /// Add an import filter.
    void addImportFilter(KwImportFilter* importFilter);

    /// Add an export filter.
    void addExportFilter(KwExportFilter* exportFilter);

    /// Get load mime types.
    QStringList loadMimeTypes() const;

    /// Get save mime types.
    QStringList saveMimeTypes() const;

    /// Get import mime types.
    QStringList importMimeTypes() const;

    /// Get export mime types.
    QStringList exportMimeTypes() const;

    /// Get the load filter for a mime type.
    KwLoadSaveFilter* loadFilterFromMimeType(const QString& mimeType);

    /// Get the save filter for a mime type.
    KwLoadSaveFilter* saveFilterFromMimeType(const QString& mimeType);

    /// Get the import filter for a mime type.
    KwImportFilter* importFilterFromMimeType(const QString& mimeType);

    /// Get the export filter for a mime type.
    KwExportFilter* exportFilterFromMimeType(const QString& mimeType);

  private:

    /*
     * Variables
     */

    /// Default load save filter.
    KwLoadSaveFilter* m_defaultLoadSaveFilter;

    /// List of load save filters.
    QList<KwLoadSaveFilter*> m_loadSaveFilters;

    /// List of import filters.
    QList<KwImportFilter*> m_importFilters;

    /// List of export filters.
    QList<KwExportFilter*> m_exportFilters;

    /// Hash of filters for each load mime type.
    QHash<QString, KwLoadSaveFilter*> m_loadMimeFilters;

    /// Hash of filters for each save mime type.
    QHash<QString, KwLoadSaveFilter*> m_saveMimeFilters;

    /// Hash of filters for each import mime type.
    QHash<QString, KwImportFilter*> m_importMimeFilters;

    /// Hash of filters for each export mime type.
    QHash<QString, KwExportFilter*> m_exportMimeFilters;
};

#endif // _KwFilterManager_h_
