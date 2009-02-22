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

#ifndef _KwPascalStream_h_
#define _KwPascalStream_h_

/**
 * @file KwPascalStream.h
 * @brief Provides Pascal serialization of binary data.
 * @author James Hogan <james@albanarts.com>
 */

#include <QIODevice>
#include <QList>

#include <inttypes.h>

class QByteArray;

/// Provides Pascal serialization of binary data.
class KwPascalStream
{
  public:

    /*
     * Constructors + destructor
     */

    /// Use a byte array as a buffer.
    KwPascalStream(QByteArray* a, QIODevice::OpenMode mode);

    /// Use a constant byte array as a buffer.
    KwPascalStream(const QByteArray* a);

    /// Destructor.
    virtual ~KwPascalStream();

    /*
     * Reading interface
     */

    /// Find whether we're at the end of the file.
    bool atEnd() const;

    /// Read a single byte.
    uint8_t read8();

    /// Read 2 bytes.
    uint16_t read16();

    /// Read 4 bytes.
    uint32_t read32();

    /// Read short string.
    QByteArray readString();

    /// Read long string.
    QByteArray readLString();

    /// Read wide string.
    QString readWString();

    /// Read UTF8 string.
    QString readUtf8String();

    /*
     * Writing interface
     */

    /// Write a single byte.
    void write8(uint8_t byte);

    /// Write 2 bytes.
    void write16(uint16_t word);

    /// Write 4 bytes.
    void write32(uint32_t dword);

    /// Write short string (length < 2^8).
    void writeString(const QByteArray& str);

    /// Write long string (length < 2^16).
    void writeLString(const QByteArray& str);

    /// Write UTF8 string.
    void writeUtf8String(const QString& str);

    /*
     * Property interface
     */

    /// Write a property.
    void writeProperty(const QByteArray& name, const QVariant& value);

    /// Read a property.
    void readProperty(QByteArray& name, QVariant& value);

    /// Start a list.
    void writeStartList();

    /// End a list.
    void writeEndList();

    /// Write a string in an appropriate format.
    KwPascalStream& operator << (const QString& str);

    /// Write a list of something.
    template <typename T>
    KwPascalStream& operator << (const QList<T>& list)
    {
      writeStartList();
      foreach (T item, list)
      {
        *this << item;
      }
      writeEndList();
      return *this;
    }

    /// Write a variant.
    KwPascalStream& operator << (const QVariant& var);

    /// Read a variant.
    KwPascalStream& operator >> (QVariant& var);

  private:

    /*
     * Types
     */

    enum TypeCodes
    {
      vaNull = 0,
      vaList,
      vaInt8,
      vaInt16,
      vaInt32,
      vaExtended, // 5
      vaString,
      vaIdent,
      vaFalse,
      vaTrue,
      vaBinary, // 10
      vaSet,
      vaLString,
      vaNil,
      vaCollection,
      vaSingle, // 15
      vaCurrency,
      vaDate,
      vaWString,
      vaInt64,
      vaUTF8String // 20
    };

    /*
     * Variables
     */

    /// IO Device.
    QIODevice* m_d;
};

#endif // _KwPascalStream_h_
