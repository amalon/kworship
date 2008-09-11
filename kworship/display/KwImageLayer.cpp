/**
 * @file KwImageLayer.cpp
 * @brief Background image layer.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwImageLayer.h"
#include "KwImageWidget.h"

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QStackedLayout>

/*
 * Constructors + destructors
 */

/// Default constructor.
KwImageLayer::KwImageLayer()
: KwAbstractLayer()
, m_brush()
, m_pixmap()
, m_stretch(false)
, m_keepAspect(false)
{
}

/// Primary constructor.
KwImageLayer::KwImageLayer(QBrush brush)
: KwAbstractLayer()
, m_brush(brush)
, m_pixmap()
, m_stretch(true)
, m_keepAspect(false)
{
}

/// Primary constructor.
KwImageLayer::KwImageLayer(const QPixmap& pixmap)
: KwAbstractLayer()
, m_brush()
, m_pixmap(pixmap)
, m_stretch(true)
, m_keepAspect(false)
{
}

/// Destructor.
KwImageLayer::~KwImageLayer()
{
}

/*
 * Private structures
 */

struct KwImageLayerData
{
  KwImageWidget* imageWidget;
};

/*
 * Methods
 */

void* KwImageLayer::addWidgets(QWidget* master) const
{
  KwImageLayerData* data = new KwImageLayerData;

  data->imageWidget = new KwImageWidget(m_brush, m_pixmap, m_stretch, m_keepAspect);

  QStackedLayout* layout = new QStackedLayout();
  layout->setStackingMode(QStackedLayout::StackAll);
  master->setLayout(layout);
  layout->addWidget(data->imageWidget);

  return (void*)data;
}

void KwImageLayer::removeWidgets(QWidget* master, void* rawData) const
{
  Q_UNUSED(master)

  KwImageLayerData* data = reinterpret_cast<KwImageLayerData*>(rawData);

  delete data->imageWidget;

  delete data;
}

