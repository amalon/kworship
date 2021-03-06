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

#ifndef _UpOoBackend_h_
#define _UpOoBackend_h_

/**
 * @file UpOoBackend.h
 * @brief OpenOffice.org presentation manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpBackend.h"

#include <com/sun/star/uno/Reference.h>

class UpOoBridge;

using namespace com::sun::star;

/// OpenOffice.org presentation manager.
class UpOoBackend : public UpBackend
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpOoBackend(QObject* parent = 0, const QStringList& = QStringList());

    /// Destructor.
    virtual ~UpOoBackend();

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

    /*
     * Other interfaces
     */

    /// Update the list of presentations
    void updatePresentations();

  private:

    /*
     * Types
     */

    /// Listener for document events.
    class DocumentEventListener;

    /*
     * Variables
     */

    /// Office bridge.
    UpOoBridge* m_bridge;

    /// Global document event listener.
    uno::Reference<DocumentEventListener> m_globalDocumentEventListener;

    /// List of presentations.
    QList<UpPresentation*> m_presentations;

};

#endif // _UpOoBackend_h_

