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

#ifndef _UpKpr1Backend_h_
#define _UpKpr1Backend_h_

/**
 * @file UpKpr1Backend.h
 * @brief KPresenter 1 presentation manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpBackend.h"

/** KPresenter 1 presentation manager.
 * This is a messy backend to use the DCOP interface.
 */
class UpKpr1Backend : public UpBackend
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpKpr1Backend(QObject* parent = 0);

    /// Destructor.
    virtual ~UpKpr1Backend();

    /*
     * General meta information
     */

    virtual QString name() const;

    virtual QString description() const;

    virtual QStringList mimeTypes() const;

    virtual QIcon icon() const;

    /*
     * Activation
     */

    virtual bool activate();

    virtual void deactivate();

    /*
     * Presentation management
     */

    virtual QList<UpPresentation*> presentations();

    virtual UpPresentation* openPresentation(const QUrl& url);

  private:

    /*
     * Variables
     */

    /// List of presentations.
    QList<UpPresentation*> m_presentations;

};

#endif // _UpKpr1Backend_h_
