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

#ifndef _UpSlide_h_
#define _UpSlide_h_

/**
 * @file UpSlide.h
 * @brief An abstract presentation slide.
 * @author James Hogan <james@albanarts.com>
 */

#include <QObject>
#include <QPixmap>

/** An abstract presentation slide.
 * Inherit from this class to implement each backend's presentation slide.
 */
class UpSlide : public QObject
{
  Q_OBJECT
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpSlide(QObject* parent = 0);

    /// Destructor.
    virtual ~UpSlide();

    /*
     * Main interface
     */

    // get outline
    virtual QString outline();

    // get notes outline
    virtual QString notes();

    // get preview
    virtual QPixmap preview();
};

#endif // _UpSlide_h_

