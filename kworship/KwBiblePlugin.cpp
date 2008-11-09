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
 * @file KwBiblePlugin.cpp
 * @brief Bibles plugin.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBiblePlugin.h"

#include <KwBibleManager.h>
#include <KwBibleManagerSword.h>
#include <KwBibleManagerBibleGateway.h>
#include <KwBibleModule.h>

#include <KLocale>
#include <KAction>
#include <KMessageBox>

#include <QMainWindow>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QToolBar>

/*
 * Constructors + destructor
 */

/// Default constructor.
KwBiblePlugin::KwBiblePlugin()
: KwPlugin("bible",
           i18n("Bible"),
           i18n("The bible plugin allows for the navigation and display of "
                "bible extracts from SWORD and BibleGateway.com."))
, m_managers()
, m_insertIntoPlaylistAction(0)
, m_showNowAction(0)
, m_docker(0)
, m_managerTabs(0)
, m_comboBook(0)
, m_comboChapter(0)
, m_editRange(0)
, m_textPassage(0)
{
}

/// Destructor.
KwBiblePlugin::~KwBiblePlugin()
{
  // Ensure all GUI stuff is cleaned up
  KwBiblePlugin::_unload();
}

/*
 * Private slots
 */

/// Fired when the connect to bible button is pressed.
void KwBiblePlugin::slotConnect()
{
  // Get the current bible manager
  int tab = m_managerTabs->currentIndex();
  Q_ASSERT(tab >= 0 && tab < m_managers.size());
  BibleManager* mgr = &m_managers[tab];

  // This will force the connection
  fillBiblesList(mgr);
  if (mgr->comboBibles->count() == 0)
  {
    KMessageBox::information(m_docker, i18n("No bibles found"));
  }
  else
  {
    mgr->comboBibles->setEnabled(true);
  }
}

/// Fired when the bible is changed.
void KwBiblePlugin::slotBibleChanged()
{
  // Get the current bible manager
  int tab = m_managerTabs->currentIndex();
  if (tab >= 0 && tab < m_managers.size())
  {
    BibleManager& mgr = m_managers[tab];
    bool enabled = mgr.comboBibles->isEnabled();

    // Is a bible selected?
    int bibleInd = mgr.comboBibles->currentIndex();
    QString bible;
    KwBibleModule* module = 0;
    if (bibleInd >= 0)
    {
      QString bible = mgr.comboBibles->itemData(bibleInd).toString();
      module = mgr.manager->module(bible);
    }

    // Update the list of books
    QString book = m_comboBook->currentText();
    int chapter = m_comboChapter->currentIndex();
    m_comboBook->clear();
    if (0 != module)
    {
      QStringList bookNames = module->books();
      for (int i = 0; i < bookNames.size(); ++i)
      {
        const QString& bookName = bookNames[i];
        m_comboBook->addItem(bookName, QVariant(i));
      }
      int index = m_comboBook->findText(book);
      bool canPreserveBook = (index >= 0);
      if (!canPreserveBook && bookNames.size() > 0)
      {
        index = 0;
      }
      m_comboBook->setCurrentIndex(index);
      if (canPreserveBook && chapter >= 0)
      {
        // If we can restore book, also restore chapter
        m_comboChapter->setCurrentIndex(chapter);
      }
    }
    else
    {
      enabled = false;
    }
    
    m_comboBook->setEnabled(enabled);
    m_comboChapter->setEnabled(enabled);
    m_editRange->setEnabled(enabled);
  }
}

/// Fired when the bible book is changed.
void KwBiblePlugin::slotBookChanged()
{
  m_comboChapter->clear();

  // Get the current bible manager
  int tab = m_managerTabs->currentIndex();
  if (tab >= 0 && tab < m_managers.size())
  {
    BibleManager& mgr = m_managers[tab];

    // Is a bible selected?
    int bibleInd = mgr.comboBibles->currentIndex();
    QString bible;
    KwBibleModule* module = 0;
    if (bibleInd >= 0)
    {
      QString bible = mgr.comboBibles->itemData(bibleInd).toString();
      module = mgr.manager->module(bible);
    }
    if (0 != module)
    {
      // Is a book selected?
      int index = m_comboBook->currentIndex();
      if (index >= 0)
      {
        int bookIndex = m_comboBook->itemData(index).toInt();
        int numChapters = module->numChapters(bookIndex);
        for (int i = 0; i < numChapters; ++i)
        {
          m_comboChapter->addItem(QString("%1").arg(i+1), QVariant(i));
        }
      }
    }
  }
  slotVerseRange();
}

/// Fired when the bible text needs to be retrieved.
void KwBiblePlugin::slotVerseRange()
{
  // Get the current bible manager
  int tab = m_managerTabs->currentIndex();
  if (tab >= 0 && tab < m_managers.size())
  {
    BibleManager& mgr = m_managers[tab];

    // Is a bible selected?
    int bibleInd = mgr.comboBibles->currentIndex();
    QString bible;
    KwBibleModule* module = 0;
    if (bibleInd >= 0)
    {
      QString bible = mgr.comboBibles->itemData(bibleInd).toString();
      module = mgr.manager->module(bible);
    }
    if (0 != module)
    {
      // Is a book selected?
      int bookIndex = m_comboBook->currentIndex();
      int chapterIndex = -1;
      if (bookIndex >= 0)
      {
        // Is a chapter selected?
        chapterIndex = m_comboChapter->currentIndex();
      }

      bool valid;
      KwBibleModule::Key relativeKey = module->createKey(bookIndex, chapterIndex);
      KwBibleModule::Key key = module->createKey(relativeKey, m_editRange->text(), &valid);
      // Update book and chapter
      m_comboBook->setCurrentIndex(key.start.book);
      m_comboChapter->setCurrentIndex(key.start.chapter);
      m_textPassage->document()->setHtml(module->renderText(key));

      m_insertIntoPlaylistAction->setEnabled(true);
      m_showNowAction->setEnabled(true);

      // Update color of search box
      static QPalette p = m_editRange->palette();
      QPalette changedPal = p;
      if (!valid)
      {
        changedPal.setColor( QPalette::Normal, QPalette::Base, QColor(255, 127, 127) );
      }
      m_editRange->setPalette(changedPal);

      return;
    }
  }
  m_textPassage->document()->setPlainText(QString());
  m_insertIntoPlaylistAction->setEnabled(false);
  m_showNowAction->setEnabled(false);
}

/// Fired by the insert into playlist action.
void KwBiblePlugin::slotInsertIntoPlaylist()
{
}

/// Fired by the show now action.
void KwBiblePlugin::slotShowNow()
{
}

/*
 * Loading and unloading virtual interface
 */

void KwBiblePlugin::_load(QMainWindow* mainWindow)
{
  // Construct the bible managers. 
  QList<KwBibleManager*> managers; 
  managers.push_back(new KwBibleManagerSword); 
  managers.push_back(new KwBibleManagerBibleGateway); 

  // Set up the docker
  m_docker = new QDockWidget(i18n("Bible"));
  m_docker->setObjectName("dockBible");
  QWidget* mainDockWidget = new QWidget(/*m_docker*/);
  QVBoxLayout* dockLayout = new QVBoxLayout(mainDockWidget);
  m_docker->setWidget(mainDockWidget);

  // The tab bar of bible managers
  m_managerTabs = new QTabWidget(m_docker);
  m_managerTabs->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  connect(m_managerTabs, SIGNAL(currentChanged(int)),
          this, SLOT(slotBibleChanged()));
  dockLayout->addWidget(m_managerTabs);

  // Bible navigation combo boxes
  QWidget* bibleNavigationWidget = new QWidget(mainDockWidget);
  QHBoxLayout* bibleNavigationLayout = new QHBoxLayout(bibleNavigationWidget);
  dockLayout->addWidget(bibleNavigationWidget);

  m_comboBook = new QComboBox(bibleNavigationWidget);
  m_comboChapter = new QComboBox(bibleNavigationWidget);
  bibleNavigationLayout->addWidget(m_comboBook);
  bibleNavigationLayout->addWidget(m_comboChapter);

  // Verse range text box and label
  QWidget* verseRangeWidget = new QWidget(mainDockWidget);
  QHBoxLayout* verseRangeLayout = new QHBoxLayout(verseRangeWidget);
  dockLayout->addWidget(verseRangeWidget);

  QLabel* labelRange = new QLabel(i18n("&Verses"), verseRangeWidget);
  m_editRange = new QLineEdit(verseRangeWidget);
  labelRange->setBuddy(m_editRange);
  verseRangeLayout->addWidget(labelRange);
  verseRangeLayout->addWidget(m_editRange);

  m_textPassage = new QTextEdit(mainDockWidget);
  m_textPassage->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
  dockLayout->addWidget(m_textPassage);

  // Toolbar
  QToolBar* bibleToolBar = new QToolBar("bibleToolBar");
  bibleToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  dockLayout->addWidget(bibleToolBar);

  m_insertIntoPlaylistAction = new KAction(KIcon("player_playlist"), i18n("Insert Into Playlist"), bibleToolBar);
  m_insertIntoPlaylistAction->setEnabled(false);
  connect(m_insertIntoPlaylistAction, SIGNAL(triggered(bool)),
          this, SLOT(slotInsertIntoPlaylist()));
  bibleToolBar->addAction(m_insertIntoPlaylistAction);

  m_showNowAction = new KAction(KIcon("player_playlist"), i18n("Show Now"), bibleToolBar);
  m_showNowAction->setEnabled(false);
  connect(m_showNowAction, SIGNAL(triggered(bool)),
          this, SLOT(slotShowNow()));
  bibleToolBar->addAction(m_showNowAction);
    
  // Fill out tabs and manager data
  foreach (KwBibleManager* manager, managers)
  {
    QString name = manager->name();
    BibleManager mgr;
    mgr.manager = manager;

    QWidget* tabWidget = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout(tabWidget);

    mgr.comboBibles = new QComboBox();
    connect(mgr.comboBibles, SIGNAL(currentIndexChanged(int)),
            this, SLOT(slotBibleChanged()));

    // Only fill the module list if the manager is local
    // Otherwise we should wait until the user requests it
    if (manager->isRemote())
    {
      mgr.comboBibles->setEnabled(false);
  
      mgr.toolBar = new QToolBar();
      KAction* connectToBible = new KAction(KIcon("network-connect"), i18n("Connect to %1", name), mgr.toolBar);
      connect(connectToBible, SIGNAL(triggered(bool)),
              this, SLOT(slotConnect()));
      mgr.toolBar->addAction(connectToBible);
      layout->addWidget(mgr.toolBar);

      // Toolbar should be as small as possible
      QSizePolicy policy;

      policy = mgr.toolBar->sizePolicy();
      policy.setHorizontalStretch(1);
      mgr.toolBar->setSizePolicy(policy);

      policy = mgr.comboBibles->sizePolicy();
      policy.setHorizontalStretch(10);
      mgr.comboBibles->setSizePolicy(policy);
    }
    else
    {
      mgr.toolBar = 0;
      fillBiblesList(&mgr);
    }

    layout->addWidget(mgr.comboBibles);

    m_managerTabs->addTab(tabWidget, name);
    m_managers.push_back(mgr);
  }
  // Ensure widgets are apropriately modified
  connect(m_comboBook, SIGNAL(currentIndexChanged(int)),
          this, SLOT(slotBookChanged()));
  connect(m_comboChapter, SIGNAL(currentIndexChanged(int)),
          this, SLOT(slotVerseRange()));
  connect(m_editRange, SIGNAL(textChanged(const QString&)),
          this, SLOT(slotVerseRange()));

  mainWindow->addDockWidget(Qt::LeftDockWidgetArea, m_docker);

  slotBibleChanged();
}

void KwBiblePlugin::_unload()
{
  // Clean up the bible managers.
  /// @todo IMPLEMENT!!!
  delete m_docker;
}

/*
 * Private functions
 */

/// Fill up the bibles list for a manager.
void KwBiblePlugin::fillBiblesList(BibleManager* mgr)
{
  QStringList languages = mgr->manager->languages();
  mgr->comboBibles->clear();
  mgr->comboBibles->addItem(i18n("-- select a translation --"));
  foreach (QString language, languages)
  {
    QStringList modules = mgr->manager->moduleNamesInLanguage(language);
    if (!modules.isEmpty())
    {
      mgr->comboBibles->addItem(language, QVariant(modules.first()));
      foreach (QString module, modules)
      {
        mgr->comboBibles->addItem("    " + module, QVariant(module));
      }
    }
  }
}

