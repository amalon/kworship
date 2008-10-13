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
 * @file KwResourceLink.cpp
 * @brief A link to a resource file.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwResourceLink.h"

/*
 * Constructors + destructor
 */

/// Construct a URL link.
KwResourceLink::KwResourceLink(const KUrl& url)
: m_type(Url)
, m_url(url)
, m_path()
{
}

/// Construct a path link.
KwResourceLink::KwResourceLink(Type type, const QString& path)
: m_type(type)
, m_url()
, m_path(path)
{
  Q_ASSERT(type != Url);
}

/// Destructor.
KwResourceLink::~KwResourceLink()
{
}

/*
 * Accessors
 */

/// Get the type of resource link.
KwResourceLink::Type KwResourceLink::type() const
{
  return m_type;
}

/// Get the url.
KUrl KwResourceLink::url() const
{
  Q_ASSERT(type == Url);
  return m_url;
}

/// Get the type dependent path.
QString KwResourceLink::path() const
{
  Q_ASSERT(type != Url);
  return m_path;
}

