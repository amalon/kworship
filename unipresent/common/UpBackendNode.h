/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
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

#ifndef _UpBackendNode_h_
#define _UpBackendNode_h_

/**
 * @file UpBackendNode.h
 * @brief A presentations node for a backend.
 * @author James Hogan <james@albanarts.com>
 */

#include "NodeBasedModel.h"

class UpBackend;

/// A presentations node for a backend.
class UpBackendNode : public DefaultModelNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    UpBackendNode(DefaultModelNode* parent, UpBackend* item);

    /// Destructor.
    virtual ~UpBackendNode();

    /*
     * Accessors
     */

    UpBackend* getItem();

    /*
     * Main interface
     */

    virtual QVariant getData(int role, int column);

    virtual int getChildCount() const;

  protected:

    virtual DefaultModelNode* _getChild(int index);

  private:

    /*
     * Variables
     */

    /// Playlist item.
    UpBackend* m_item;
};

#endif // _UpBackendNode_h_

