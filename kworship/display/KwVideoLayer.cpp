/***************************************************************************
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   This file is part of KWorship.                                        *
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
 * @file KwVideoLayer.cpp
 * @brief Background video layer.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwVideoLayer.h"

#include "KwMediaManager.h"

#include <phonon/videowidget.h>

#include <QStackedLayout>

/*
 * Constructors + destructors
 */

/// Primary constructor.
KwVideoLayer::KwVideoLayer(KwMediaManager* mediaManager)
: KwAbstractLayer()
, m_mediaManager(mediaManager)
, m_stretch(false)
, m_keepAspect(false)
{
}

/// Destructor.
KwVideoLayer::~KwVideoLayer()
{
}

/*
 * Private structures
 */

struct KwVideoLayerData
{
  Phonon::VideoWidget* widget;
};

/*
 * Methods
 */

void* KwVideoLayer::addWidgets(QWidget* master) const
{
  KwVideoLayerData* data = new KwVideoLayerData;

  data->widget = new Phonon::VideoWidget(master);
  m_mediaManager->linkVideo(data->widget);
  data->widget->setAspectRatio(Phonon::VideoWidget::AspectRatioWidget);

  QStackedLayout* layout = new QStackedLayout(master);
  layout->setStackingMode(QStackedLayout::StackAll);
  master->setLayout(layout);
  layout->addWidget(data->widget);

  return (void*)data;
}

void KwVideoLayer::removeWidgets(QWidget* master, void* rawData) const
{
  Q_UNUSED(master)

  KwVideoLayerData* data = reinterpret_cast<KwVideoLayerData*>(rawData);

  m_mediaManager->unlinkVideo(data->widget);
  delete data->widget;

  delete data;
}

