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

/**
 * @file KwFilterManager.cpp
 * @brief Manages file filters.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwFilterManager.h"
#include "KwLoadSaveFilter.h"

/*
 * Constructors + destructor
 */

/// Primary constructor.
KwFilterManager::KwFilterManager()
: m_defaultLoadSaveFilter(0)
, m_loadSaveFilters()
, m_importFilters()
, m_exportFilters()
, m_loadMimeFilters()
, m_saveMimeFilters()
, m_importMimeFilters()
, m_exportMimeFilters()
, m_defaultSaveMimeType()
{
}

/// Destructor.
KwFilterManager::~KwFilterManager()
{
  // Delete all filters.
  foreach (KwLoadSaveFilter* filter, m_loadSaveFilters)
  {
    delete filter;
  }
  foreach (KwImportFilter* filter, m_importFilters)
  {
    delete filter;
  }
  foreach (KwExportFilter* filter, m_exportFilters)
  {
    delete filter;
  }
}

/*
 * Main interface
 */

/// Add a load save filter.
void KwFilterManager::addLoadSaveFilter(KwLoadSaveFilter* loadSaveFilter, bool makeDefault)
{
  m_loadSaveFilters += loadSaveFilter;

  // Update hashes of filters for each mime type
  QStringList mimes = loadSaveFilter->importMimeTypes();
  foreach (QString mime, mimes)
  {
    m_loadMimeFilters[mime] = loadSaveFilter;
  }
  mimes = loadSaveFilter->exportMimeTypes();
  foreach (QString mime, mimes)
  {
    m_saveMimeFilters[mime] = loadSaveFilter;
  }

  if (makeDefault)
  {
    m_defaultLoadSaveFilter = loadSaveFilter;
    Q_ASSERT(mimes.size() >= 1);
    m_defaultSaveMimeType = mimes[0];
  }
}

/// Add an import filter.
void KwFilterManager::addImportFilter(KwImportFilter* importFilter)
{
  m_importFilters += importFilter;

  // Update hash of import filters for each mime type
  QStringList mimes = importFilter->importMimeTypes();
  foreach (QString mime, mimes)
  {
    m_importMimeFilters[mime] = importFilter;
  }
}

/// Add an export filter.
void KwFilterManager::addExportFilter(KwExportFilter* exportFilter)
{
  m_exportFilters += exportFilter;

  // Update hash of export filters for each mime type
  QStringList mimes = exportFilter->exportMimeTypes();
  foreach (QString mime, mimes)
  {
    m_exportMimeFilters[mime] = exportFilter;
  }
}

/// Get load mime types.
QStringList KwFilterManager::loadMimeTypes() const
{
  return m_loadMimeFilters.keys();
}

/// Get save mime types.
QStringList KwFilterManager::saveMimeTypes() const
{
  return m_saveMimeFilters.keys();
}

/// Get import mime types.
QStringList KwFilterManager::importMimeTypes() const
{
  return m_importMimeFilters.keys();
}

/// Get export mime types.
QStringList KwFilterManager::exportMimeTypes() const
{
  return m_exportMimeFilters.keys();
}

/// Get the default save mime type.
const QString& KwFilterManager::defaultSaveMimeType() const
{
  return m_defaultSaveMimeType;
}

/// Get the load filter for a mime type.
KwLoadSaveFilter* KwFilterManager::loadFilterFromMimeType(const QString& mimeType)
{
  if (m_loadMimeFilters.contains(mimeType))
  {
    return m_loadMimeFilters[mimeType];
  }
  else
  {
    return 0;
  }
}

/// Get the save filter for a mime type.
KwLoadSaveFilter* KwFilterManager::saveFilterFromMimeType(const QString& mimeType)
{
  if (m_saveMimeFilters.contains(mimeType))
  {
    return m_saveMimeFilters[mimeType];
  }
  else
  {
    return 0;
  }
}

/// Get the import filter for a mime type.
KwImportFilter* KwFilterManager::importFilterFromMimeType(const QString& mimeType)
{
  if (m_importMimeFilters.contains(mimeType))
  {
    return m_importMimeFilters[mimeType];
  }
  else
  {
    return 0;
  }
}

/// Get the export filter for a mime type.
KwExportFilter* KwFilterManager::exportFilterFromMimeType(const QString& mimeType)
{
  if (m_exportMimeFilters.contains(mimeType))
  {
    return m_exportMimeFilters[mimeType];
  }
  else
  {
    return 0;
  }
}
