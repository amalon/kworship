/**
 * @file KwVideoLayer.cpp
 * @brief Background video layer.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwVideoLayer.h"

#include <phonon/mediaobject.h>
#include <phonon/videowidget.h>

#include <QStackedLayout>

/*
 * Constructors + destructors
 */

/// Primary constructor.
KwVideoLayer::KwVideoLayer(Phonon::MediaObject* media)
: KwAbstractLayer()
, m_media(media)
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
  Phonon::createPath(m_media, data->widget);
  data->widget->setAspectRatio(Phonon::VideoWidget::AspectRatioWidget);

  QStackedLayout* layout = new QStackedLayout();
  layout->setStackingMode(QStackedLayout::StackAll);
  layout->addWidget(data->widget);
  master->setLayout(layout);

  return (void*)data;
}

void KwVideoLayer::removeWidgets(QWidget* master, void* rawData) const
{
  Q_UNUSED(master)

  KwVideoLayerData* data = reinterpret_cast<KwVideoLayerData*>(rawData);

  delete data->widget;

  delete data;
}

