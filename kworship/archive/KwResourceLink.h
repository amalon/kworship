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

#ifndef _KwResourceLink_h_
#define _KwResourceLink_h_

/**
 * @file KwResourceLink.h
 * @brief A link to a resource file.
 * @author James Hogan <james@albanarts.com>
 */

#include <KUrl>

class KwResourceManager;

class QDomDocument;
class QDomElement;

/// A link to a resource file.
class KwResourceLink
{
  public:

    /*
     * Types
     */

    /// Type of resource link.
    enum Type {
      Null,            ///< Invalid.
      Url,             ///< URL link.
      FileRelative,    ///< Path relative to the save file.
      ArchiveRoot,     ///< Path relative to the archive root.
      ArchiveRelative  ///< Path relative to the referencer in the archive.
    };

    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwResourceLink();

    /// Construct from a DOM element.
    KwResourceLink(const QDomElement& element, KwResourceManager* resourceManager);

    /** Construct a URL link.
     * @param url URL to the resource.
     */
    KwResourceLink(const KUrl& url);

    /** Construct a path link.
     * @param type Type of path (must not be Url).
     * @param path Path of whatever type to the resource.
     */
    KwResourceLink(Type type, const QString& path);

    /// Destructor.
    ~KwResourceLink();

    /*
     * DOM Translation
     */

    /// Export this resource link into a DOM.
    void exportToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const;

    /*
     * Accessors
     */

    /// Get whether the link is null.
    bool isNull() const;

    /// Get the type of resource link.
    Type type() const;

    /// Get the url.
    KUrl url() const;

    /// Get the type dependent path.
    QString path() const;

  private:

    /*
     * Variables
     */

    /// Type of link.
    Type m_type;

    /// URL to resource.
    KUrl m_url;

    /// Path to resource depending on type.
    QString m_path;
};

#endif // _KwResourceLink_h_

