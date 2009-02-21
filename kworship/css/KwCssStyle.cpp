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
 * @file KwCssStyle.cpp
 * @brief Typed cascading style property.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssStyle.h"

#include <QRegExp>

#include "KwCssUnprocessed.h"
template <>
KwCssUnprocessed KwCssStringify<KwCssUnprocessed>(const KwCssUnprocessed& value)
{
  return value;
}
template <>
KwCssUnprocessed KwCssUnstringify<KwCssUnprocessed>(const KwCssUnprocessed& value, bool* success)
{
  *success = true;
  return value;
}

// Primitives
template <>
KwCssUnprocessed KwCssStringify<bool>(const bool& value)
{
  return KwCssUnprocessed(value ? "true" : "false");
}
template <>
bool KwCssUnstringify<bool>(const KwCssUnprocessed& value, bool* success)
{
  if (value == "true")
  {
    *success = true;
    return true;
  }
  else if (value == "false")
  {
    *success = true;
    return false;
  }
  else
  {
    *success = false;
    return false;
  }
}

template <>
KwCssUnprocessed KwCssStringify<int>(const int& value)
{
  return KwCssUnprocessed::number(value);
}
template <>
int KwCssUnstringify<int>(const KwCssUnprocessed& value, bool* success)
{
  return value.toInt(success);
}

template <>
KwCssUnprocessed KwCssStringify<float>(const float& value)
{
  return KwCssUnprocessed::number(value);
}
template <>
float KwCssUnstringify<float>(const KwCssUnprocessed& value, bool* success)
{
  return value.toFloat(success);
}

template <>
KwCssUnprocessed KwCssStringify<double>(const double& value)
{
  return KwCssUnprocessed::number(value);
}
template <>
double KwCssUnstringify<double>(const KwCssUnprocessed& value, bool* success)
{
  return value.toDouble(success);
}

#include <KwResourceLink.h>
template <>
KwCssUnprocessed KwCssStringify<KwResourceLink>(const KwResourceLink& value)
{
  switch (value.type())
  {
    case KwResourceLink::Url:
    {
      QString url = value.url().url();
      url.replace('\\', "\\\\")
         .replace('"', "\\\"");
      return QString("\"%1\"").arg(url);
    }

    case KwResourceLink::FileRelative:
    {
      QString url = value.path();
      url.replace('\\', "\\\\")
         .replace('"', "\\\"");
      return QString("frel \"%1\"").arg(url);
    }

    case KwResourceLink::ArchiveRoot:
    {
      QString url = value.path();
      url.replace('\\', "\\\\")
         .replace('"', "\\\"");
      return QString("aroot \"%1\"").arg(url);
    }

    case KwResourceLink::ArchiveRelative:
    {
      QString url = value.path();
      url.replace('\\', "\\\\")
         .replace('"', "\\\"");
      return QString("arel \"%1\"").arg(url);
    }

    case KwResourceLink::Null:
    default:
    {
      return "null";
    }

  }
}
template <>
KwResourceLink KwCssUnstringify<KwResourceLink>(const KwCssUnprocessed& value, bool* success)
{
  if ("null" != value)
  {
    static QRegExp reFormat("((\\w*)\\s+)?\"((\\.|[^\\\"])*)\"");
    static const QRegExp reUnescape("\\(.)");
    static const QString unescapeReplace("\\1");
    if (reFormat.exactMatch(value))
    {
      QString keyword = reFormat.cap(1);
      QString file = reFormat.cap(3);
      file.replace(reUnescape, unescapeReplace);
      *success = true;
      if (keyword.isEmpty())
      {
        return KwResourceLink(KUrl(file));
      }
      else if ("frel" == keyword)
      {
        return KwResourceLink(KwResourceLink::FileRelative, file);
      }
      else if ("aroot" == keyword)
      {
        return KwResourceLink(KwResourceLink::ArchiveRoot, file);
      }
      else if ("arel" == keyword)
      {
        return KwResourceLink(KwResourceLink::ArchiveRelative, file);
      }
    }
  }
  *success = false;
  return KwResourceLink();
}

#include <QBrush>
template <>
KwCssUnprocessed KwCssStringify<QBrush>(const QBrush& value)
{
  return "Brush()";
}
template <>
QBrush KwCssUnstringify<QBrush>(const KwCssUnprocessed& value, bool* success)
{
  *success = true; 
  return QBrush(Qt::black);
}

#include <QPen>
template <>
KwCssUnprocessed KwCssStringify<QPen>(const QPen& value)
{
  return "Pen()";
}
template <>
QPen KwCssUnstringify<QPen>(const KwCssUnprocessed& value, bool* success)
{
  *success = true; 
  return QPen();
}

#include <QFont>
template <>
KwCssUnprocessed KwCssStringify<QFont>(const QFont& value)
{
  return "Font()";
}
template <>
QFont KwCssUnstringify<QFont>(const KwCssUnprocessed& value, bool* success)
{
  *success = true; 
  return QFont();
}
