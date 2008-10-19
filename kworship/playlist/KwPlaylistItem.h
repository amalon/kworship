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

#ifndef _KwPlaylistItem_h_
#define _KwPlaylistItem_h_

/**
 * @file KwPlaylistItem.h
 * @brief An item that can be added to a playlist.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssScope.h"
#include "Factory.h"

#include <QString>
#include <QList>
#include <QDomDocument>
#include <QDomDocumentFragment>

class KwResourceManager;
class KwResourceLink;
class KwPlaylistItem;
class KwPlaylistNode;

#define KW_PLAYLIST_ITEM \
  private: \
    /* \
     * Static private variables \
     */ \
    static bool s_registered;

#define KW_REGISTER_PLAYLIST_ITEM(X, KEY) \
  bool X::s_registered = KwPlaylistItem::factory()->addType< X >(KEY);

/// An item that can be added to a playlist.
/**
 * Inherit from this class for each playlist item type.
 */
class KwPlaylistItem : public KwCssScope
{
  public:

    /*
     * Item factory
     */

    /// Factory of items identified by strings and constructed from DOM.
    typedef ::Factory<QString, KwPlaylistItem, META_TUPLE((const QDomElement&, KwResourceManager*))> Factory;

    /// Get a factory object.
    static Factory* factory();
    
    /*
     * Constructors + destructor.
     */

    /// Default constructor.
    KwPlaylistItem();

    /// Construct from a DOM element.
    KwPlaylistItem(const QDomElement& element, KwResourceManager* resourceManager);

    /// Destructor.
    virtual ~KwPlaylistItem();

    /*
     * DOM Translation.
     */

    /// Create an item from a DOM element.
    static KwPlaylistItem* createFromDom(const QDomElement& element, KwResourceManager* resourceManager);

    /// Export this item to the DOM.
    void exportToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const;

    /// Get the type of the item.
    virtual QString itemType() const = 0;

    /// Export details of this item to the DOM.
    virtual void exportDetailsToDom(QDomDocument& document, QDomElement& element, KwResourceManager* resourceManager) const = 0;

    /*
     * Main interface.
     */

    /// Get a tree node for this item.
    virtual KwPlaylistNode* getNode(KwPlaylistNode* parent) = 0;

  protected:

    /*
     * Protected methods
     */

    /** Indicate that elements of a particular tag name have been handled.
     * This clears the specified elements from the DOM preserve.
     */
    void elementsHandled(const QString& tagName);

    /** Indicate that the first elements of a particular tag name have been handled.
     * This clears the specified element from the DOM preserve.
     */
    void elementHandled(const QString& tagName);

    /** Get a resource by name.
     * @param name Name of resource.
     * @param create If true the resource link is created if it doesn't exist.
     */
    KwResourceLink* getResource(const QString& name, bool create = true);

    /** Set a resource associated with a name.
     * @param name Name of resource.
     * @param link Link to associate with @p name.
     */
    KwResourceLink* setResource(const QString& name, KwResourceLink* link);

    /** Delete a resource.
     * @param name Name of resource to delete.
     */
    void deleteResource(const QString& name);

  private:

    /*
     * Types
     */

    /// Resource information.
    struct Resource
    {
      QString name;
      KwResourceLink* link;
    };
    typedef QList<Resource> Resources;

    /*
     * Variables
     */

    /// Document to store fragment in.
    QDomDocument m_domDocument;

    /// Fragment of DOM from save file which needs preserving.
    QDomDocumentFragment m_domPreserve;

    /// Resources.
    Resources m_resources;
};

#endif // _KwPlaylistItem_h_

