/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   KWorship is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   KWorship is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with KWorship.  If not, see <http://www.gnu.org/licenses/>.     *
 ***************************************************************************/

/**
 * @file DesktopView.cpp
 * @brief Preview of the screens on the desktop.
 * @author James Hogan <james@albanarts.com>
 */

#include "DesktopView.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QMouseEvent>

#include <cassert>

/*
 * Constructors + destructor
 */

/// Primary constructor.
DesktopView::DesktopView(QWidget* parent)
: QGraphicsView(parent)
, m_desktopRect()
, m_multiSelect(false)
, m_noSelect(true)
, m_selectedScreen(-1)
, m_selectedScreens()
{
  setup();
}

/// Destructor.
DesktopView::~DesktopView()
{
}

/*
 * Main interface
 */

/// Find whether a screen is selected.
bool DesktopView::isScreenSelected(int screen) const
{
  assert(screen >= 0 && screen < m_selectedScreens.size());
  if (m_multiSelect)
  {
    return m_selectedScreens[screen];
  }
  else
  {
    return (screen == m_selectedScreen);
  }
}

/// Find which single screen is selected.
int DesktopView::selectedScreen() const
{
  if (m_multiSelect)
  {
    /// @todo Implement multiselect selectedScreen()
    return -1;
  }
  else
  {
    return m_selectedScreen;
  }
}

/*
 * Public slots
 */

/// Set the selected screen.
void DesktopView::setSelectedScreen(int selectedScreen)
{
  if (m_multiSelect)
  {
    /// @todo Implement multiselect setSelectedScreen(int)
  }
  else if (m_selectedScreen != selectedScreen)
  {
    screenSelected(m_selectedScreen, false);
    m_selectedScreen = selectedScreen;
    screenSelected(m_selectedScreen, true);
    singleSelectRestatus();
    setup();
  }
}

/*
 * Events
 */

void DesktopView::resizeEvent(QResizeEvent*)
{
  fitInView(m_desktopRect, Qt::KeepAspectRatio);
}

void DesktopView::mousePressEvent(QMouseEvent* event)
{
  if (isEnabled())
  {
    QDesktopWidget* desktop = qobject_cast<QApplication*>(QCoreApplication::instance())->desktop();
    if (0 != itemAt(event->pos()))
    {
      QPoint pos = mapToScene(event->pos()).toPoint();
      int screen = desktop->screenNumber(pos);
      assert(screen >= 0 && screen < m_selectedScreens.size());

      if (m_multiSelect)
      {
        if (event->modifiers().testFlag(Qt::ControlModifier))
        {
          // We know its changed here so no need to use selectScreen
          screenSelected(screen, m_selectedScreens[screen] = !m_selectedScreens[screen]);
        }
        else
        {
          for (int i = 0; i < m_selectedScreens.size(); ++i)
          {
            selectScreen(i, i == screen);
          }
        }
      }
      else if (m_selectedScreen != screen)
      {
        if (m_selectedScreen >= 0)
        {
          screenSelected(m_selectedScreen, false);
        }
        m_selectedScreen = screen;
        screenSelected(m_selectedScreen, true);
        singleSelectRestatus();
      }
    }
    else
    {
      if (m_multiSelect)
      {
        if (!event->modifiers().testFlag(Qt::ControlModifier))
        {
          for (int i = 0; i < m_selectedScreens.size(); ++i)
          {
            selectScreen(i, false);
          }
        }
      }
      else if (m_noSelect && m_selectedScreen >= 0)
      {
        screenSelected(m_selectedScreen, false);
        m_selectedScreen = -1;
        singleSelectRestatus();
      }
    }
    setup();
  }
  QGraphicsView::mousePressEvent(event);
}

/*
 * Private slots
 */

/// Indicates that a screen has been resized.
void DesktopView::resizeScreen(int screen)
{
  Q_UNUSED(screen)
  setup();
}

/*
 * Private functions
 */

/// Setup the display.
void DesktopView::setup()
{
  QDesktopWidget* desktop = qobject_cast<QApplication*>(QCoreApplication::instance())->desktop();
  assert(0 != desktop);
  int screens = desktop->numScreens();
  assert(0 != screens);
  int primary = desktop->primaryScreen();

  // Cleanup any previous scene
  delete scene();

  int oldSize = m_selectedScreens.size();
  m_selectedScreens.resize(screens);
  if (m_multiSelect)
  {
    while (oldSize < screens)
    {
      m_selectedScreens[oldSize] = false;
      ++oldSize;
    }
  }

  // Set up the screens preview
  QGraphicsScene* scene = new QGraphicsScene(this);
  setScene(scene);

  for (int i = 0; i < screens; ++i)
  {
    QRectF geom = desktop->screenGeometry(i);

    // rectangle
    QGraphicsRectItem* rect = scene->addRect(geom, QPen(Qt::black),
                                             isScreenSelected(i)   ? Qt::blue :
                                             QBrush((primary == i) ? Qt::gray :
                                             Qt::lightGray));

    // text
    QString string;
    string.setNum(i+1);
    QGraphicsTextItem* text = new QGraphicsTextItem(string, rect);

    QFont font;
    font.setPixelSize(geom.height() * 0.8f);
    text->setFont(font);

    QRectF textRect = text->boundingRect();
    text->setPos(QPointF(geom.x() + (geom.width()  - textRect.width()) / 2,
                         geom.y() + (geom.height() - textRect.height()) / 2));
  }
  m_desktopRect = desktop->rect();
  resizeEvent(0);
}

/// Change selection of a screen.
void DesktopView::selectScreen(int screen, bool newSelected)
{
  assert(m_multiSelect);
  assert(screen >= 0 && screen < m_selectedScreens.size());
  if (m_selectedScreens[screen] != newSelected)
  {
    screenSelected(screen, m_selectedScreens[screen] = newSelected);
  }
}

/// Update a single selection status.
void DesktopView::singleSelectRestatus()
{
  assert(!m_multiSelect);
  if (m_selectedScreen >= 0)
  {
    QDesktopWidget* desktop = qobject_cast<QApplication*>(QCoreApplication::instance())->desktop();
    assert(0 != desktop);
    if (m_selectedScreen < m_selectedScreens.size())
    {
      QRectF geom = desktop->screenGeometry(m_selectedScreen);
      statusChanged(tr("Screen %1: \%2x%3.")
                    .arg(m_selectedScreen+1)
                    .arg(geom.width())
                    .arg(geom.height()));
    }
    else
    {
      statusChanged(tr("Screen %1: not plugged in.")
                    .arg(m_selectedScreen+1));
    }
  }
  else
  {
    statusChanged("");
  }
  screenChanged(m_selectedScreen);
}

