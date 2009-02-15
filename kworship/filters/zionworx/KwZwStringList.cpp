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
 * @file KwZwStringList.cpp
 * @brief String list encoding widget.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwZwStringList.h"

#include <KLocale>

#include <QDataStream>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFile>

KwZwStringList::KwZwStringList()
: m_list()
, m_edit(new QLineEdit(this))
, m_output(new QTextEdit(this))
{
  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addWidget(m_edit);

  QPushButton* btnAdd = new QPushButton(i18n("Add string"), this);
  layout->addWidget(btnAdd);
  connect(btnAdd, SIGNAL(clicked(bool)), this, SLOT(addItem()));

  layout->addWidget(m_output);
  m_output->setReadOnly(true);
}

QByteArray KwZwStringList::encodeList(const QStringList& stringlist)
{
  QByteArray result;

  // Type of object
  QByteArray type = "Strings";
  result.append((char)type.size());
  result.append(type);

  // Not sure what this byte is for, perhaps the number of bytes to represent something
  char sep = '\x06';
  result.append((char)0x01);

  // Each item
  foreach (QString item, stringlist)
  {
    /// @todo Check the assumption that lines are encoded in utf-8
    QByteArray encoded = item.toUtf8();
    /// @todo Find what to do if length >= 255
    Q_ASSERT(encoded.size() < 255);
    // Length followed by string encoding
    result.append(sep);
    char size = encoded.size();
    result.append(QByteArray::fromRawData(&size, 1));
    result.append(encoded);
  }
  result.append('\0');
  return result;
}

void KwZwStringList::addItem()
{
  m_list += m_edit->text();
  m_edit->setText("");
  m_output->setText(m_list.join("\n"));

  QByteArray result = encodeList(m_list);
  {
    QFile op("dump");
    op.open(QIODevice::WriteOnly);
    op.write(result);
  }
  {
    QFile op("dump.base64");
    op.open(QIODevice::WriteOnly);
    op.write(result.toBase64());
  }
}
