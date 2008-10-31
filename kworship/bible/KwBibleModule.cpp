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
 * @file KwBibleModule.cpp
 * @brief A bible module (analagous to a SWORD module).
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBibleModule.h"

#include <QStringList>

#include <swmodule.h>
#include <versekey.h>

/*
 * Constructors + destructor
 */

/// Default constructor.
KwBibleModule::KwBibleModule(sword::SWModule* module)
: m_module(module)
{
}

/// Destructor.
KwBibleModule::~KwBibleModule()
{
}

/*
 * Main interface
 */

/// Get the name of the module.
QString KwBibleModule::name() const
{
  return m_module->Name();
}

/// Get the description of the module.
QString KwBibleModule::description() const
{
  return m_module->Description();
}

/// Get rendered text for a given passage.
QString KwBibleModule::renderText(const QString& key) const
{
  QStringList bits = key.split('-');
  sword::VerseKey vkey;
  if (bits.size() >= 2)
  {
    vkey = sword::VerseKey(bits[0].toAscii(), bits[1].toAscii());
  }
  else
  {
    vkey = sword::VerseKey(key.toAscii(), key.toAscii());
  }

  QString result;
  sword::VerseKey verse = vkey.LowerBound();
  verse.Headings(1);
  sword::VerseKey last = vkey.UpperBound();
  Q_ASSERT(verse.isTraversable());

  int limit = 100;
  for (; verse.compare(last) <= 0; verse.increment(1))
  {
    m_module->setKey(&verse);
    m_module->RenderText();
    const char* preverse = m_module->getEntryAttributes()["Heading"]["Preverse"]["0"];
    result += " ";
    if (preverse[0] != '\0')
    {
      result += QString("<h1>%1</h1>").arg(QString::fromUtf8(preverse));
    }
    result += QString("<sup>%1</sup>").arg(verse.Verse()) + QString::fromUtf8(m_module->RenderText());
    if (0 == --limit)
    {
      break;
    }
  }

  return result;
}

