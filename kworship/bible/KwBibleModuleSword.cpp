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
 * @file KwBibleModuleSword.cpp
 * @brief A SWORD bible module.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBibleModuleSword.h"

#include <QStringList>

#include <swmodule.h>
#include <versekey.h>

/*
 * Constructors + destructor
 */

/// Default constructor.
KwBibleModuleSword::KwBibleModuleSword(sword::SWModule* module)
: KwBibleModule()
, m_module(module)
{
}

/// Destructor.
KwBibleModuleSword::~KwBibleModuleSword()
{
}

/*
 * Main interface
 */

QString KwBibleModuleSword::name()
{
  return m_module->Name();
}

QString KwBibleModuleSword::description()
{
  return m_module->Description();
}

int KwBibleModuleSword::numChapters(int book)
{
  return 0;
}

int KwBibleModuleSword::numVerses(int book, int chapter)
{
  return 0;
}

QString KwBibleModuleSword::renderText(const KwBibleModule::Key& key)
{
  sword::VerseKey vkey;
  vkey.LowerBound().Book(key.start.book);
  vkey.LowerBound().Chapter(key.start.chapter);
  vkey.LowerBound().Verse(key.start.verse);
  vkey.UpperBound().Book(key.end.book);
  vkey.UpperBound().Chapter(key.end.chapter);
  vkey.UpperBound().Verse(key.end.verse);

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

/*
 * Protected virtual interface
 */

void KwBibleModuleSword::obtainBooks()
{
  setBooks(QStringList());
}

