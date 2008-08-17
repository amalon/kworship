/**
 * @file KwImageLayer.cpp
 * @brief Background image layer.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwImageLayer.h"

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QStackedLayout>

/*
 * Constructors + destructors
 */

/// Default constructor.
KwImageLayer::KwImageLayer()
: KwAbstractLayer()
, m_pixmap()
, m_stretch(false)
{
}

/// Primary constructor.
KwImageLayer::KwImageLayer(const QPixmap& pixmap)
: KwAbstractLayer()
, m_pixmap(pixmap)
, m_stretch(true)
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
  QGraphicsView*       graphicsView;
  QGraphicsScene*      graphicsScene;
  QGraphicsPixmapItem* graphicsPixmap;
};

/*
 * Methods
 */

void* KwImageLayer::addWidgets(QWidget* master) const
{
  KwImageLayerData* data = new KwImageLayerData;

  data->graphicsView   = new QGraphicsView();
  data->graphicsView->setFrameShape(QFrame::NoFrame);
  data->graphicsView->setFrameShadow(QFrame::Plain);
  data->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  data->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  data->graphicsView->setBackgroundBrush(QBrush(Qt::black));

  data->graphicsScene  = new QGraphicsScene();
  data->graphicsView->setScene(data->graphicsScene);

  data->graphicsPixmap = data->graphicsScene->addPixmap(m_pixmap);
  data->graphicsPixmap->update(0, 0, m_pixmap.width(), m_pixmap.height());

  QStackedLayout* layout = new QStackedLayout();
  layout->setStackingMode(QStackedLayout::StackAll);
  layout->addWidget(data->graphicsView);
  master->setLayout(layout);

  if (m_stretch)
  {
  }

  return (void*)data;
}

void KwImageLayer::removeWidgets(QWidget* master, void* rawData) const
{
  KwImageLayerData* data = reinterpret_cast<KwImageLayerData*>(rawData);

  delete data->graphicsView;
  delete data->graphicsScene;

  delete data;
}

