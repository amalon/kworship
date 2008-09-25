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

#ifndef _UpBackend_h_
#define _UpBackend_h_

/**
 * @file UpBackend.h
 * @brief An abstract presentation manager.
 * @author James Hogan <james@albanarts.com>
 */

#include <QObject>
#include <QString>
#include <QStringList>
#include <QUrl>

class UpPresentation;

/** An abstract presentation manager.
 * Inherit from this class to implement each backend.
 */
class UpBackend : public QObject
{
  Q_OBJECT
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpBackend(QObject* parent = 0);

    /// Destructor.
    virtual ~UpBackend();

    /*
     * General meta information
     */

    /// Get the name of the backend.
    virtual QString name() const = 0;

    /// Get a description of the backend.
    virtual QString description() const = 0;

    /// Get a list of supported mime types.
    virtual QStringList mimeTypes() const = 0;

    /*
     * Activation
     */

    /** Ensure that the backend is active and ready.
     * @return Whether the activation worked.
     */
    virtual bool activate() = 0;

    /// Deactivate the backend.
    virtual void deactivate() = 0;

    /*
     * Presentation management
     */

    /// Get a list of presentations.
    virtual QList<UpPresentation*> presentations() = 0;

    /// Open a new presentation.
    virtual UpPresentation* openPresentation(const QUrl& url) = 0;

  signals:

    /*
     * Signals
     */

    /// Fired when the backend is activated.
    void activated();

    /// Fired when the backend is deactivated.
    void deactivated();

    /// Fired when a new presentation is created or loaded.
    void loadedPresentation(UpPresentation*);

    /// Fired when a presentation is saved under a new name.
    void savedAsPresentation(UpPresentation*);

    /// Fired when a presentation is about to be closed.
    void unloadedPresentation(UpPresentation*);
};

#endif // _UpBackend_h_

