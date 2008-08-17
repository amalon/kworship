/**
 * @file KwLocalDisplayPreview.cpp
 * @brief Wrapper around KwLocalDisplay to allow scaling preview.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwLocalDisplayPreview.h"

#include <QGraphicsProxyWidget>

/*
 * Constructors + destructors
 */

/// Primary constructor.
KwLocalDisplayPreview::KwLocalDisplayPreview(QWidget* parent)
: QGraphicsView(parent)
, KwAbstractDisplay()
, m_isPrimary(false)
, m_scene(0)
, m_display(0)
, m_displayProxy(0)
{
  // Set up graphics view
  setFrameShape(QFrame::NoFrame);
  setFrameShadow(QFrame::Plain);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // Set up contents of scene
  m_scene = new QGraphicsScene;
  setScene(m_scene);

  m_display = new KwLocalDisplay;
  attachChild(m_display);
  m_displayProxy = m_scene->addWidget(m_display);
  m_displayProxy->resize(getDisplayResolution());

  setBackgroundBrush(QBrush(Qt::darkGray));
  resizeEvent(0);
}

/// Destructor.
KwLocalDisplayPreview::~KwLocalDisplayPreview()
{
  delete m_scene;
}

/*
 * Public methods
 */

/// Set whether this preview is the primary display.
void KwLocalDisplayPreview::setPrimary(bool newIsPrimary)
{
  m_isPrimary = newIsPrimary;
  resizeEvent(0);
}

/*
 * Main interface events for extension
 */

void KwLocalDisplayPreview::setDisplayResolutionEvent(QSize size)
{
  resizeContents(size, this->size());
}

void KwLocalDisplayPreview::clearLayersEvent()
{
}

void KwLocalDisplayPreview::setLayerEvent(unsigned int index, const KwAbstractLayer* layer, bool insert)
{
}

void KwLocalDisplayPreview::removeLayerEvent(unsigned int index)
{
}

/*
 * QT Events
 */

void KwLocalDisplayPreview::resizeEvent(QResizeEvent*)
{
  if (m_isPrimary)
  {
    getHighestParent()->setDisplayResolution(size());
  }
  resizeContents(getDisplayResolution(), size());
}

/*
 * Private methods
 */

/// Resize contents.
void KwLocalDisplayPreview::resizeContents(QSize fullSize, QSize localSize)
{
  QSizeF viewportSize = fullSize;
  float localAspect = (float)localSize.width() / localSize.height();
  float fullAspect = (float)viewportSize.width() / viewportSize.height();
  if (localAspect > fullAspect)
  {
    viewportSize.setWidth((float)viewportSize.height() * localAspect);
  }
  else
  {
    viewportSize.setHeight((float)viewportSize.width() / localAspect);
  }

  m_displayProxy->setPos(-0.5f * fullSize.width(), -0.5f * fullSize.height());
  m_displayProxy->resize(fullSize);

  resetMatrix();
  fitInView(-0.5f * viewportSize.width(),
            -0.5f * viewportSize.height(),
            viewportSize.width(),
            viewportSize.height());
}

