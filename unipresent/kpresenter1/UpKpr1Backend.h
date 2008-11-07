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

#ifndef _UpKpr1Backend_h_
#define _UpKpr1Backend_h_

/**
 * @file UpKpr1Backend.h
 * @brief KPresenter 1 presentation manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpBackend.h"

class QTimer;
class QStringList;

/** KPresenter 1 presentation manager.
 * This is a messy backend to use the DCOP interface.
 */
class UpKpr1Backend : public UpBackend
{
    Q_OBJECT

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

    virtual QString id() const;
    virtual QString name() const;
    virtual QString description() const;
    virtual QStringList mimeTypes() const;
    virtual QIcon icon() const;

    /*
     * Activation
     */

    virtual bool isActive();
    virtual bool activate();
    virtual void deactivate();

    /*
     * Presentation management
     */

    virtual QList<UpPresentation*> presentations();
    virtual bool openPresentation(const QUrl& url);

  private slots:

    /*
     * Private slots
     */

    /// Hit at intervals to refresh presentation list.
    void refresh();

  private:

    /*
     * Private functions
     */

    /// Find a presentation identified by a dcop reference.
    UpPresentation* presentationByDcop(const QStringList& dcopRef) const;

    /*
     * Variables
     */

    /// List of presentations.
    QList<UpPresentation*> m_presentations;

    /// Refresh timer.
    QTimer* m_refreshTimer;
};

#endif // _UpKpr1Backend_h_

