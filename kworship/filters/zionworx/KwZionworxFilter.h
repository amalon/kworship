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

#ifndef _KwZionworxFilter_h_
#define _KwZionworxFilter_h_

/**
 * @file KwZionworxFilter.h
 * @brief Main Zionworx load and save filter.
 * @author James Hogan <james@albanarts.com>
 */

#include <KwLoadSaveFilter.h>

#include <QStringList>
#include <QColor>

class QDomElement;

/// Main Zionworx load and save filter.
class KwZionworxFilter : public KwLoadSaveFilter
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    KwZionworxFilter();

    /// Destructor.
    virtual ~KwZionworxFilter();

    /*
     * Main interface
     */
    
    /// Reimplemented.
    virtual KwDocument* load(const KUrl& url, const QString& mimeType);

    /// Reimplemented.
    virtual bool save(KwDocument* doc, const KUrl& url, const QString& mimeType);

  protected:

    /*
     * Virtual interface
     */

    /// Reimplemented.
    virtual void v_saveLimitations(KwDocument* doc, const QString& mimeType, Limitations* o_limitations);

  private:

    /*
     * Private classes
     */

    /// Contains implementations of export functions.
    class ExportToDom;

    /*
     * Private functions
     */

    /// Read a TTntStringList from DOM.
    QStringList readStringList(const QDomElement& el) const;

    /// Read a colour from DOM.
    QColor readColour(const QDomElement& el, bool* ok = 0) const;
};

#endif // _KwZionworxFilter_h_
