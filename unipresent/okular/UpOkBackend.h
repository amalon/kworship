/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008-2009 James Hogan <james@albanarts.com>                 *
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

#ifndef _UpOkBackend_h_
#define _UpOkBackend_h_

/**
 * @file UpOkBackend.h
 * @brief Okular presentation manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpBackend.h"

#include <QHash>

class UpOkProcess;
class UpOkPresentation;

/** Okular presentation manager.
 * This uses a nice dbus interface.
 */
class UpOkBackend : public UpBackend
{
    Q_OBJECT

  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpOkBackend(QObject* parent = 0, const QStringList& params = QStringList());

    /// Destructor.
    virtual ~UpOkBackend();

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

    // Slots for UpOkProcess signals
    void dbusLoadedPresentation(UpOkPresentation*);
    void dbusUnloadedPresentation(UpOkPresentation*);

  private:

    /*
     * Variables
     */

    typedef QHash<QString,UpOkProcess*> QStringHashProcess;
    /// The okular processes.
    QStringHashProcess m_processes;

    /// List of presentations.
    QList<UpPresentation*> m_presentations;

};

#endif // _UpOkBackend_h_
