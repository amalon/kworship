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
#include <QIcon>

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

    /// Get the internal name of the backend.
    virtual QString id() const = 0;

    /// Get the name of the backend.
    virtual QString name() const = 0;

    /// Get a description of the backend.
    virtual QString description() const = 0;

    /// Get a list of supported mime types.
    virtual QStringList mimeTypes() const = 0;

    /// Get an icon for this backend.
    virtual QIcon icon() const = 0;

    /*
     * Activation
     */

    /** Find whether the backend is active and ready.
     * @return Whether activated.
     */
    virtual bool isActive() = 0;

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
    virtual bool openPresentation(const QUrl& url) = 0;

  signals:

    /*
     * Signals
     */

    /// Emitted when the backend is activated.
    void activated();

    /// Emitted when the backend is deactivated.
    void deactivated();

    /// Emitted when a new presentation is created or loaded.
    void loadedPresentation(UpPresentation*);

    /// Emitted when a presentation is changed to a different url.
    void movedPresentation(UpPresentation*);

    /// Emitted when a presentation is about to be closed.
    void unloadedPresentation(UpPresentation*);
};

#endif // _UpBackend_h_

