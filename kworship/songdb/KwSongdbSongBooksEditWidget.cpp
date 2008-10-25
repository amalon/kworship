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
 * @file KwSongdbSongBooksEditWidget.cpp
 * @brief Widget for editing song books.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbSongBooksEditWidget.h"

#include <KAction>
#include <KDialog>

#include <QToolBar>
#include <QPointer>

/*
 * Static
 */

/// Show the edit song books dialog.
KwSongdbSongBooksEditWidget* KwSongdbSongBooksEditWidget::showDialog()
{
  static QPointer<KDialog> dialog;
  static QPointer<KwSongdbSongBooksEditWidget> view;

  if (0 == dialog)
  {
    dialog = new KDialog();
    view = new KwSongdbSongBooksEditWidget();
    dialog->setMainWidget(view);
    dialog->setButtons(KDialog::Ok | KDialog::Cancel | KDialog::Apply);

    connect(dialog, SIGNAL(applyClicked()),
            view, SLOT(save()));
    connect(dialog, SIGNAL(okClicked()),
            view, SLOT(save()));
    connect(view, SIGNAL(changed(bool)),
            dialog, SLOT(enableButtonApply(bool)));

    dialog->enableButtonApply(false);
    dialog->setAttribute(Qt::WA_DeleteOnClose, true);
    dialog->show();
  }
  else
  {
    dialog->activateWindow();
    dialog->raise();
  }


  return view;
}

/*
 * Constructors + destructor
 */

/// Default constructor.
KwSongdbSongBooksEditWidget::KwSongdbSongBooksEditWidget()
: QWidget()
, Ui::KwSongdbSongBooksEditWidget_base()
{
  setupUi(this);

  // Song books toolbar
  QToolBar* songBooksToolBar = new QToolBar("songBooksToolBar");
  layoutSongBooksToolBar->layout()->addWidget(songBooksToolBar);
  {
    KAction* addAction = new KAction(KIcon("list-add"), i18n("Add Song Book"), songBooksToolBar);
    connect(addAction, SIGNAL(triggered(bool)),
            this, SLOT(addSongBook()));
    songBooksToolBar->addAction(addAction);

    KAction* removeAction = new KAction(KIcon("list-remove"), i18n("Remove Song Book"), songBooksToolBar);
    connect(removeAction, SIGNAL(triggered(bool)),
            this, SLOT(removeSongBook()));
    songBooksToolBar->addAction(removeAction);
  }

  // Signals
  connect(listSongBooks, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
          this, SLOT(songBookChanged(QListWidgetItem*, QListWidgetItem*)));

}

/// Destructor.
KwSongdbSongBooksEditWidget::~KwSongdbSongBooksEditWidget()
{
}

/*
 * Saving and loading
 */

/// Save to database.
void KwSongdbSongBooksEditWidget::save()
{
  // Versions
  for (int i = 0; i < listSongBooks->count(); ++i)
  {
    //KwSongdbSongBookItem* item = dynamic_cast<KwSongdbSongBookItem*>(listSongBooks->item(i));
    //Q_ASSERT(0 != item);
    //item->save(m_song);
  }
}

/// Add a song book.
void KwSongdbSongBooksEditWidget::addSongBook()
{
  //KwSongdbSongBookItem* item = new KwSongdbSongBookItem(listSongBooks);
  //listSongBooks->setCurrentItem(item);
}

/*
 * Private slots
 */

/// A different song book has been selected.
void KwSongdbSongBooksEditWidget::songBookChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
  /*KwSongdbSongBooksItem* previousVersion = dynamic_cast<KwSongdbSongBooksItem*>(previous);
  KwSongdbSongBooksItem* currentVersion = dynamic_cast<KwSongdbSongBooksItem*>(current);
  
  if (0 != previousVersion)
  {
  }

  if (0 != currentVersion)
  {
  }
  groupSongBook->setEnabled(0 != currentVersion);*/
}

/// Remove the selected song book.
void KwSongdbSongBooksEditWidget::removeSongBook()
{
}

