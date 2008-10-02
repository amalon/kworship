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

#ifndef _UpManager_h_
#define _UpManager_h_

/**
 * @file UpManager.h
 * @brief Overall unipresent manager.
 * @author James Hogan <james@albanarts.com>
 */

#include <QObject>
#include <QUrl>

class UpBackend;
class UpPresentation;
class UpPresentationsModel;

/// Overall unipresent manager.
class UpManager : public QObject
{
  Q_OBJECT
  public:

    /*
     * Singleton access.
     */

    /// Get the singleton object.
    static UpManager* self();

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpManager(QObject* parent = 0);

    /// Destructor.
    virtual ~UpManager();

    /*
     * Presentation management
     */

    /// Get a list of presentations.
    QList<UpPresentation*> presentations();

    /// Get a presentations model.
    UpPresentationsModel* presentationsModel();

    /// Open a new presentation.
    UpPresentation* openPresentation(const QUrl& url);

    /*
     * Backend management
     */

    /// Get the number of backends.
    int numBackends() const;

    /// Get a specific backend.
    UpBackend* backend(int index);

    /// Get a list of backends.
    QList<UpBackend*> backends();

    /// Add a backend object.
    void addBackend(UpBackend* backend);

    /** Register a new backend.
     * @param T The type of the backend.
     */
    template <class T>
    void registerBackend()
    {
      addBackend(new T(this));
    }

  private:

    /*
     * Static variables
     */

    /// Singleton object.
    static UpManager* s_singleton;

    /*
     * Variables
     */

    /// Backends.
    QList<UpBackend*> m_backends;

    /// Presentations model.
    UpPresentationsModel* m_presentationsModel;

};

#endif // _UpManager_h_

