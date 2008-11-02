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

/**
 * @file KwBibleModuleBibleGateway.cpp
 * @brief A BibleGateway bible module.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBibleModuleBibleGateway.h"

#include <QStringList>

/*
 * Constructors + destructor
 */

/// Default constructor.
KwBibleModuleBibleGateway::KwBibleModuleBibleGateway(int id)
: KwBibleModule()
{
}

/// Destructor.
KwBibleModuleBibleGateway::~KwBibleModuleBibleGateway()
{
}

/*
 * Main interface
 */

QString KwBibleModuleBibleGateway::name()
{
  return QString();
}

QString KwBibleModuleBibleGateway::description()
{
  return QString();
}

int KwBibleModuleBibleGateway::numChapters(int book)
{
  return 0;
}

int KwBibleModuleBibleGateway::numVerses(int book, int chapter)
{
  return 0;
}

QString KwBibleModuleBibleGateway::renderText(const KwBibleModule::Key& key)
{
  return QString();
}

/*
 * Protected virtual interface
 */

void KwBibleModuleBibleGateway::obtainBooks()
{
  setBooks(QStringList());
}

