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

#ifndef _UpOkProcess_h_
#define _UpOkProcess_h_

/**
 * @file UpOkProcess.h
 * @brief Okular process.
 * @author James Hogan <james@albanarts.com>
 */

#include <QObject>
#include <QHash>

class UpPresentation;
class UpOkBackend;
class UpOkPresentation;

/** Okular process.
 * This corresponds to a KPresenter dbus service.
 */
class UpOkProcess : public QObject
{
    Q_OBJECT

  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpOkProcess(QString serviceName, UpOkBackend* parent = 0);

    /// Destructor.
    virtual ~UpOkProcess();

    /*
     * Basic accessors
     */

    /// Get the service name.
    QString serviceName() const;

    /// Get a list of presentations.
    QList<UpOkPresentation*> presentations();

  signals:

    /*
     * Signals
     */

    /// Emitted when a new presentation is created or loaded.
    void loadedPresentation(UpOkPresentation*);

    /// Emitted when a presentation is about to be closed.
    void unloadedPresentation(UpOkPresentation*);

  private slots:

    /*
     * Private slots
     */

    /// Indicates that a new presentation has been made available.
    void dbusPresentationOpened(QString docName);

    /// Indicates that an old presentation is no longer available.
    void dbusPresentationClosed(QString docName);

  private:

    /*
     * Variables
     */

    /// Backend object.
    UpOkBackend* m_backend;

    /// DBus service name.
    QString m_serviceName;

    typedef QHash<QString, UpOkPresentation*> StringHashPresentation;
    /// Presentations by name.
    StringHashPresentation m_presentations;

};

#endif // _UpOkProcess_h_

