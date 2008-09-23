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

#ifndef _UpOoimpManager_h_
#define _UpOoimpManager_h_

/**
 * @file UpOoimpManager.h
 * @brief OpenOffice.org Impress presentation manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpManager.h"

/// OpenOffice.org Impress presentation manager.
class UpOoimpManager : public UpManager
{
  Q_OBJECT
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpOoimpManager(QObject* parent = 0);

    /// Destructor.
    virtual ~UpOoimpManager();

    /*
     * General meta information
     */

    virtual QString name() const;

    virtual QString description() const;

    virtual QStringList mimeTypes() const;

    /*
     * Presentation management
     */

    virtual QList<UpPresentation*> presentations();

    virtual UpPresentation* openPresentation(const QUrl& url);

};

#endif // _UpOoimpManager_h_

