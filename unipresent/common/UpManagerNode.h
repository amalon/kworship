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

#ifndef _UpManagerNode_h_
#define _UpManagerNode_h_

/**
 * @file UpManagerNode.h
 * @brief A presentations node for the manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "NodeBasedModel.h"

class UpManager;

/// A presentations node for the manager.
class UpManagerNode : public DefaultModelNode
{
  public:
    
    /*
     * Constructors + destructor.
     */

    /// Primary constructor.
    UpManagerNode(DefaultModelNode* parent, UpManager* item);

    /// Destructor.
    virtual ~UpManagerNode();

    /*
     * Accessors
     */

    UpManager* getItem();

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
    UpManager* m_item;
};

#endif // _UpManagerNode_h_

