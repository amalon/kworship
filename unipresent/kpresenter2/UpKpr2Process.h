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

#ifndef _UpKpr2Process_h_
#define _UpKpr2Process_h_

/**
 * @file UpKpr2Process.h
 * @brief KPresenter 2 process.
 * @author James Hogan <james@albanarts.com>
 */

#include <QObject>
#include <QHash>

class UpPresentation;
class UpKpr2Backend;
class UpKpr2Presentation;

/** KPresenter 2 process.
 * This corresponds to a KPresenter dbus service.
 */
class UpKpr2Process : public QObject
{
    Q_OBJECT

  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpKpr2Process(QString serviceName, UpKpr2Backend* parent = 0);

    /// Destructor.
    virtual ~UpKpr2Process();

    /*
     * Basic accessors
     */

    /// Get the service name.
    QString serviceName() const;

    /// Get a list of presentations.
    QList<UpKpr2Presentation*> presentations();

  signals:

    /*
     * Signals
     */

    /// Emitted when a new presentation is created or loaded.
    void loadedPresentation(UpKpr2Presentation*);

    /// Emitted when a presentation is about to be closed.
    void unloadedPresentation(UpKpr2Presentation*);

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
    UpKpr2Backend* m_backend;

    /// DBus service name.
    QString m_serviceName;

    typedef QHash<QString, UpKpr2Presentation*> StringHashPresentation;
    /// Presentations by name.
    StringHashPresentation m_presentations;

};

#endif // _UpKpr2Process_h_

