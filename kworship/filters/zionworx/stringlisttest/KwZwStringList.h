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

#ifndef _KwZwStringList_h_
#define _KwZwStringList_h_

/**
 * @file KwZwStringList.h
 * @brief String list encoding widget.
 * @author James Hogan <james@albanarts.com>
 */

#include <QStringList>
#include <QByteArray>
#include <QWidget>

class QLineEdit;
class QTextEdit;

/// String list encoding widget.
class KwZwStringList : public QWidget
{
    Q_OBJECT

  public:

    KwZwStringList();

    static QByteArray encodeList(const QStringList& stringList);

  public slots:

    void addItem();

  private:

    QStringList m_list;
    QLineEdit* m_edit;
    QTextEdit* m_output;
};

#endif // _KwZwStringList_h_

