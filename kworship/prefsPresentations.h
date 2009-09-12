/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2009 James Hogan <james@albanarts.com>                      *
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

#ifndef _prefsPresentations_h_
#define _prefsPresentations_h_

/**
 * @file prefsPresentations.h
 * @brief Presentations preferences interface.
 * @author James Hogan <james@albanarts.com>
 */

#include <QtGui/QWidget>

#include "ui_prefsPresentations_base.h"

/// Presentations preferences interface.
class prefsPresentations : public QWidget, public Ui::prefsPresentations_base
{
  Q_OBJECT
  public:

    /*
     * Constructors + destructor
     */

    /// Primary constructor.
    prefsPresentations(QWidget *parent);

    /// Destructor.
    virtual ~prefsPresentations();
};

#endif // _prefsPresentations_h_
