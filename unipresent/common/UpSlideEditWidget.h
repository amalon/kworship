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

#ifndef _UpSlideEditWidget_h_
#define _UpSlideEditWidget_h_

/**
 * @file UpSlideEditWidget.h
 * @brief An abstract presentation slide editor.
 * @author James Hogan <james@albanarts.com>
 */

#include <QWidget>

/** An abstract presentation slide preview.
 * Inherit from this class to implement each backend's presentation slide
 * editor.
 */
class UpSlideEditWidget : public QWidget
{
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    UpSlideEditWidget(QWidget* parent = 0);

    /// Destructor.
    virtual ~UpSlideEditWidget();
};

#endif // _UpSlideEditWidget_h_

