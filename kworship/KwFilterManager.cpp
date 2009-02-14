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
  if (makeDefault)
  {
    m_defaultLoadSaveFilter = loadSaveFilter;
  }
}

/// Add an import filter.
void KwFilterManager::addImportFilter(KwImportFilter* importFilter)
{
  m_importFilters += importFilter;
}

/// Add an export filter.
void KwFilterManager::addExportFilter(KwExportFilter* exportFilter)
{
  m_exportFilters += exportFilter;
}

/// Get load mime types.
QStringList KwFilterManager::loadMimeTypes() const
{
  QStringList result;
  foreach (KwLoadSaveFilter* filter, m_loadSaveFilters)
  {
    result += filter->importMimeTypes();
  }
  return result;
}

/// Get save mime types.
QStringList KwFilterManager::saveMimeTypes() const
{
  QStringList result;
  foreach (KwLoadSaveFilter* filter, m_loadSaveFilters)
  {
    result += filter->exportMimeTypes();
  }
  return result;
}

/// Get import mime types.
QStringList KwFilterManager::importMimeTypes() const
{
  QStringList result;
  foreach (KwImportFilter* filter, m_importFilters)
  {
    result += filter->importMimeTypes();
  }
  return result;
}

/// Get export mime types.
QStringList KwFilterManager::exportMimeTypes() const
{
  QStringList result;
  foreach (KwExportFilter* filter, m_exportFilters)
  {
    result += filter->exportMimeTypes();
  }
  return result;
}
