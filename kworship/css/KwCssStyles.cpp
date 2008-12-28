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
 * @file KwCssStyles.cpp
 * @brief Set of cascading style properties.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssStyles.h"
#include "KwCssStyleStates.h"
#include "KwCssAbstractStyle.h"
#include "KwCssAbstractStyleState.h"

#include <QRegExp>

/*
 * Constructors + destructors
 */

/// Default constructor.
KwCssStyles::KwCssStyles()
: m_styles()
{
}

/// Copy constructor.
KwCssStyles::KwCssStyles(const KwCssStyles& other)
: m_styles()
{
  StyleDictionary::const_iterator it;
  for (it = other.m_styles.begin(); it != other.m_styles.end(); ++it)
  {
    m_styles[it.key()] = (*it)->duplicate();
  }
}

/// Destructor.
KwCssStyles::~KwCssStyles()
{
  StyleDictionary::iterator it;
  for (it = m_styles.begin(); it != m_styles.end(); ++it)
  {
    delete *it;
  }
}

/*
 * Main interface
 */

/// Set a style.
void KwCssStyles::setRawStyle(QString name, KwCssAbstractStyle* style)
{
  // Delete previous value
  StyleDictionary::iterator it = m_styles.find(name);
  if (it != m_styles.end())
  {
    delete *it;
  }
  // Set new value
  m_styles[name] = style;
}

/// Return whether the styles container is empty.
bool KwCssStyles::isEmpty() const
{
  return m_styles.isEmpty();
}

/// Convert to CSS-like format.
QString KwCssStyles::toString() const
{
  static const QString tmplt = "%1 : %2;\n";
  QString result;
  StyleDictionary::const_iterator it;
  for (it = m_styles.constBegin(); it != m_styles.constEnd(); ++it)
  {
    result += tmplt.arg(it.key()).arg((*it)->toString());
  }
  return result;
}

/// Import from CSS-like format into the sheet.
int KwCssStyles::import(const QString& sheet, int start)
{
  // Read the styles
  static QRegExp reStyle("^([\\w.]+)\\s*:\\s*(\\S[^;]*);\\s*");
  int last = start;
  while (-1 != (start = reStyle.indexIn(sheet, last, QRegExp::CaretAtOffset)))
  {
    last = start + reStyle.matchedLength();
    QString name = reStyle.cap(1);
    KwCssUnprocessed value = reStyle.cap(2);
    setStyle<KwCssUnprocessed>(name, value);
  }
  return last;
}

/*
 * Operators
 */

/// Apply styles.
KwCssStyleStates& operator << (KwCssStyleStates& states, const KwCssStyles& styles)
{
  // go through styles, adjusting the states
  KwCssStyles::StyleDictionary::const_iterator it;
  for (it = styles.m_styles.begin(); it != styles.m_styles.end(); ++it)
  {
    KwCssAbstractStyleState*& state = states[it.key()];
    if (0 == state)
    {
      state = (*it)->getNewState();
    }
    (*state) << (*it);
  }
  return states;
}

