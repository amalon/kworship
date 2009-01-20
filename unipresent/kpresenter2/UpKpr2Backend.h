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

#ifndef _UpKpr2Backend_h_
#define _UpKpr2Backend_h_

/**
 * @file UpKpr2Backend.h
 * @brief KPresenter 2 presentation manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpBackend.h"

#include <QHash>

class UpKpr2Process;
class UpKpr2Presentation;

/** KPresenter 2 presentation manager.
 * This uses a nice dbus interface.
 */
class UpKpr2Backend : public UpBackend
{
    Q_OBJECT

  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpKpr2Backend(QObject* parent = 0, const QStringList& params = QStringList());

    /// Destructor.
    virtual ~UpKpr2Backend();

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

    /// DBus service ownership change.
    void dbusServiceOwnerChange(const QString& name, const QString& oldOwner, const QString& newOwner);

    // Slots for UpKpr2Process signals
    void dbusLoadedPresentation(UpKpr2Presentation*);
    void dbusUnloadedPresentation(UpKpr2Presentation*);

  private:

    /*
     * Variables
     */

    typedef QHash<QString,UpKpr2Process*> QStringHashProcess;
    /// The kpresenter processes.
    QStringHashProcess m_processes;

    /// List of presentations.
    QList<UpPresentation*> m_presentations;

};

#endif // _UpKpr2Backend_h_

