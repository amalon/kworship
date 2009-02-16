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
 * @file KwPascalStream.cpp
 * @brief Provides Pascal serialization of binary data.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPascalStream.h"

#include <QtEndian>
#include <QBuffer>
#include <QVariant>

/*
 * Constructors + destructor
 */

/// Use a byte array as a buffer.
KwPascalStream::KwPascalStream(QByteArray* a, QIODevice::OpenMode mode)
: m_d(new QBuffer(a))
{
  m_d->open(mode);
}

/// Use a constant byte array as a buffer.
KwPascalStream::KwPascalStream(const QByteArray* a)
: m_d(new QBuffer((QByteArray*)a))
{
  m_d->open(QIODevice::ReadOnly);
}

/// Destructor.
KwPascalStream::~KwPascalStream()
{
  delete m_d;
}

/*
 * Reading interface
 */

/// Find whether we're at the end of the file.
bool KwPascalStream::atEnd() const
{
  return m_d->atEnd();
}

/// Read a single byte.
uint8_t KwPascalStream::read8()
{
  uint8_t result;
  m_d->read((char*)&result, 1);
  return result;
}

/// Read 2 bytes.
uint16_t KwPascalStream::read16()
{
  uint16_t result;
  m_d->read((char*)&result, 2);
  return qFromLittleEndian(result);
}

/// Read 4 bytes.
uint32_t KwPascalStream::read32()
{
  uint32_t result;
  m_d->read((char*)&result, 4);
  return qFromLittleEndian(result);
}

/// Read short string.
QByteArray KwPascalStream::readString()
{
  uint8_t len = read8();
  return m_d->read(len);
}

/// Read long string.
QByteArray KwPascalStream::readLString()
{
  uint32_t len = read32();
  return m_d->read(len);
}

/// Read UTF8 string.
QString KwPascalStream::readUtf8String()
{
  return QString::fromUtf8(readLString());
}

/*
 * Writing interface
 */

/// Write a single byte.
void KwPascalStream::write8(uint8_t byte)
{
  m_d->write((char*)&byte,1);
}

/// Write 2 bytes.
void KwPascalStream::write16(uint16_t word)
{
  word = qToLittleEndian(word);
  m_d->write((char*)&word, 2);
}

/// Write 4 bytes.
void KwPascalStream::write32(uint32_t dword)
{
  dword = qToLittleEndian(dword);
  m_d->write((char*)&dword, 4);
}

/// Write short string (length < 2^8).
void KwPascalStream::writeString(const QByteArray& str)
{
  int len = str.size();
  if (len > 0xff)
  {
    len = 0xff;
  }
  write8(len);
  m_d->write(str, len);
}

/// Write long string.
void KwPascalStream::writeLString(const QByteArray& str)
{
  unsigned int len = str.size();
  write32(len);
  m_d->write(str, len);
}

/// Write UTF8 string.
void KwPascalStream::writeUtf8String(const QString& str)
{
  writeLString(str.toUtf8());
}

/*
 * Property interface
 */

/// Write a property.
void KwPascalStream::writeProperty(const QByteArray& name, const QVariant& value)
{
  writeString(name);
  *this << value;
}

/// Read a property.
void KwPascalStream::readProperty(QByteArray& name, QVariant& value)
{
  name = readString();
  *this >> value;
}

/// Start a list.
void KwPascalStream::writeStartList()
{
  write8(vaList);
}

/// End a list.
void KwPascalStream::writeEndList()
{
  write8(vaNull);
}

/// Write a string in an appropriate format.
KwPascalStream& KwPascalStream::operator << (const QString& str)
{
  if (str.size() == str.toUtf8().size())
  {
    if (str.size() < 0x100)
    {
      write8(vaString);
      writeString(str.toLatin1());
    }
    else
    {
      write8(vaLString);
      writeLString(str.toLatin1());
    }
  }
  else
  {
    write8(vaUTF8String);
    writeUtf8String(str);
  }
  return *this;
}

/// Write a variant.
KwPascalStream& KwPascalStream::operator << (const QVariant& var)
{
  switch (var.type())
  {
    case QVariant::List:
      *this << var.toList();
      break;
    case QVariant::String:
      *this << var.toString();
      break;
    default:
      Q_ASSERT(!"Unimplemented variant type");
      break;
  }
  return *this;
}

/// Read a variant.
KwPascalStream& KwPascalStream::operator >> (QVariant& var)
{
  // Read the type byte
  int8_t type = read8();
  switch (type)
  {
    case vaNull:
      var = QVariant(); 
      break;
    case vaList:
      {
        QVariantList list;
        QVariant item;
        while (true)
        {
          *this >> item;
          if (!item.isValid())
          {
            break;
          }
          list += item;
        }
        var = list;
      }
      break;
    case vaInt8:
      var = (int8_t)read8();
      break;
    case vaInt16:
      var = (int16_t)read16();
      break;
    case vaInt32:
      var = (int32_t)read32();
      break;
    case vaExtended:
      /// @todo Implement missing readers
      var = 0;
      break;
    case vaString:
      var = QString::fromLatin1(readString());
      break;
    case vaIdent:
      /// @todo Implement missing readers
      var = 0;
      break;
    case vaFalse:
      var = false;
      break;
    case vaTrue:
      var = true;
      break;
    case vaBinary:
    case vaSet:
      /// @todo Implement missing readers
      var = 0;
      break;
    case vaLString:
      var = QString::fromLatin1(readLString());
      break;
    case vaNil:
    case vaCollection:
    case vaSingle:
    case vaCurrency:
    case vaDate:
    case vaWString:
    case vaInt64:
      /// @todo Implement missing readers
      var = 0;
      break;
    case vaUTF8String:
      var = readUtf8String();
      break;
    default:
      var = 0;
      break;
  };
  return *this;
}
