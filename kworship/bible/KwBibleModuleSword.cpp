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
#include <swtext.h>
#include <versekey.h>

/*
 * Constructors + destructor
 */

/// Default constructor.
KwBibleModuleSword::KwBibleModuleSword(sword::SWText* module)
: KwBibleModule()
, m_module(module)
{
  m_hasTestament[0] = m_hasTestament[1] = -1;
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
  int result = 0;
  int testament = bookInTestament(book); // book gets changed
  if (testament >= 0)
  {
    sword::VerseKey key = m_module->getKey();
    result = key.books[testament][book].chapmax;
  }
  return result;
}

int KwBibleModuleSword::numVerses(int book, int chapter)
{
  int result = 0;
  int testament = bookInTestament(book); // book gets changed
  if (testament >= 0)
  {
    sword::VerseKey key = m_module->getKey();
    if (chapter < key.books[testament][book].chapmax)
    {
      result = key.books[testament][book].versemax[chapter];
    }
  }
  return result;
}

QString KwBibleModuleSword::renderText(const KwBibleModule::Key& key)
{
  QString result;
  int startBook = key.start.book;
  int endBook = key.start.book;
  int startTestament = bookInTestament(startBook); // book gets changed
  int endTestament = bookInTestament(endBook); // book gets changed
  if (startTestament >= 0)
  {
    if (endTestament == -1)
    {
      endTestament = startTestament;
      endBook = startBook;
    }
    int startChapter = key.start.chapter;
    int endChapter = key.start.chapter;
    if (startChapter < 0)
    {
      startChapter = 0;
      endChapter = numChapters(toBookIndex(endTestament, endBook))-1;
    }
    else if (endChapter < 0)
    {
      endChapter = startChapter;
    }

    int startVerse = key.start.verse;
    int endVerse = key.start.verse;
    if (startVerse < 0)
    {
      startVerse = 0;
      endVerse = numVerses(toBookIndex(endTestament, endBook), endChapter)-1;
    }
    else if (endVerse < 0)
    {
      endVerse = startVerse;
    }

    sword::VerseKey vkey;
    vkey.LowerBound().Testament(1+startTestament);
    vkey.LowerBound().Book(1+startBook);
    vkey.LowerBound().Chapter(1+startChapter);
    vkey.LowerBound().Verse(1+startVerse);
    vkey.UpperBound().Testament(1+endTestament);
    vkey.UpperBound().Book(1+endBook);
    vkey.UpperBound().Chapter(1+endChapter);
    vkey.UpperBound().Verse(1+endVerse);
    //std::cout << startTestament << " " << startBook << " " << startChapter << ":" << startVerse << std::endl;
    //std::cout << endTestament << " " << endBook << " " << endChapter << ":" << endVerse << std::endl;

    sword::VerseKey verse = vkey.LowerBound();
    verse.Headings(1);
    sword::VerseKey last = vkey.UpperBound();
    Q_ASSERT(verse.isTraversable());

    // verse must be before last
    if (verse.compare(last) <= 0)
    {
      int limit = 500;
      while (--limit > 0)
      {
        m_module->setKey(&verse);
        const char* text = m_module->RenderText();
        const char* preverse = m_module->getEntryAttributes()["Heading"]["Preverse"]["0"];
        result += " ";
        if (preverse[0] != '\0')
        {
          result += QString("<h1>%1</h1>").arg(QString::fromUtf8(preverse));
        }
        result += QString("<sup>%1</sup>").arg(verse.Verse()) + QString::fromUtf8(text);
        if (verse.equals(last))
        {
          break;
        }
        verse.increment(1);
      }
    }
  }

  return result;
}

/*
 * Protected virtual interface
 */

void KwBibleModuleSword::obtainBooks()
{
  // List books
  QStringList books; 
  sword::VerseKey key = m_module->getKey();
  for (int testament = 0; testament < 2; ++testament)
  {
    if (hasTestament(testament))
    {
      for (int book = 0; book < key.BMAX[testament]; ++book)
      {
        books << QString::fromUtf8(key.books[testament][book].name);
      }
    }
  }
  setBooks(books);
}

/*
 * Internal functions
 */

/// Find whether the module has a given testament.
bool KwBibleModuleSword::hasTestament(int testament)
{
  Q_ASSERT(testament >= 0 && testament < 2);
  if (m_hasTestament[testament] < 0)
  {
    bool oldSCL = m_module->getSkipConsecutiveLinks();
    m_module->setSkipConsecutiveLinks(true);

    m_module->setPosition((testament == 0) ? sword::TOP : sword::BOTTOM);
    sword::VerseKey key = m_module->KeyText();
    m_hasTestament[testament] = (key.Testament() == (testament+1)) ? 1 : 0;

    m_module->setSkipConsecutiveLinks(oldSCL);
  }
  return m_hasTestament[testament] != 0;
}

/// Find the index of the book within the testament.
int KwBibleModuleSword::bookInTestament(int& book)
{
  sword::VerseKey key = m_module->getKey();
  if (book >= 0)
  {
    // Old testament?
    if (book < key.BMAX[0] && hasTestament(0))
    {
      return 0;
    }
    // New testament with old testament?
    else if ( book < key.BMAX[0]+key.BMAX[1] && hasTestament(0) && hasTestament(1))
    {
      book -= key.BMAX[0];
      return 1;
    }
    // New testament without old testament?
    else if ( book < key.BMAX[1] && !hasTestament(0) && hasTestament(1))
    {
      return 1;
    }
  }
  return -1;
}

/// Find the book index from testament and book id.
int KwBibleModuleSword::toBookIndex(int testament, int book)
{
  Q_ASSERT(testament >= 0 && testament < 2);
  if (0 == testament || !hasTestament(0))
  {
    return book;
  }
  else
  {
    sword::VerseKey key = m_module->getKey();
    return key.BMAX[0] + book;
  }
  
}

