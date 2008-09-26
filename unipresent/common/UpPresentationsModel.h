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

#ifndef _UpPresentationsModel_h_
#define _UpPresentationsModel_h_

/**
 * @file UpPresentationsModel.h
 * @brief A Qt model for presentation items.
 * @author James Hogan <james@albanarts.com>
 */

#include "NodeBasedModel.h"

class QObject;

/// A Qt model for presentation items.
class UpPresentationsModel : public NodeBasedModel<>
{
  public:
    
    /*
     * Constructors + destructor
     */

    /// Default constructor.
    UpPresentationsModel(QObject* parent = 0);

    /// Destructor.
    ~UpPresentationsModel();
};

#endif // _UpPresentationsModel_h_

