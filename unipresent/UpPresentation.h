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

#ifndef _UpPresentation_h_
#define _UpPresentation_h_

/**
 * @file UpPresentation.h
 * @brief An abstract presentation document.
 * @author James Hogan <james@albanarts.com>
 */

#include <QObject>

class UpSlide;

/** An abstract presentation document.
 * Inherit from this class to implement each backend's presentation.
 */
class UpPresentation : public QObject
{
  Q_OBJECT
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpPresentation(QObject* parent = 0);

    /// Destructor.
    virtual ~UpPresentation();

    /*
     * Main interface
     */

    /// Close this presentation.
    virtual void close() = 0;

    /*
     * Slides
     */

    /// Get the number of slides in this presentation.
    virtual int numSlides() = 0;

    /// Get a specific slide.
    virtual UpSlide* getSlide(int) = 0;
};

#endif // _UpPresentation_h_

