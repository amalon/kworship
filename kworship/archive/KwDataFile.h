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

#ifndef _KwDataFile_h_
#define _KwDataFile_h_

/**
 * @file KwDataFile.h
 * @brief A KWorship XML data file.
 * @author James Hogan <james@albanarts.com>
 */

class QIODevice;
class QTextStream;
class QDomDocument;

/// A KWorship XML data file.
class KwDataFile
{
  public:

    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwDataFile();

    /// Destructor.
    virtual ~KwDataFile();

    /*
     * Reading and writing
     */

    /// Read from device.
    void readFrom(QIODevice* device);

    /// Write to stream.
    void writeTo(QTextStream& stream) const;

  private:

    /*
     * Variables
     */

    /// DOM document.
    QDomDocument* m_domDocument;

};

#endif // _KwDataFile_h_

