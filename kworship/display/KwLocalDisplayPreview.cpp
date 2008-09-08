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
  Q_UNUSED(index)
  Q_UNUSED(layer)
  Q_UNUSED(insert)
}

void KwLocalDisplayPreview::removeLayerEvent(unsigned int index)
{
  Q_UNUSED(index)
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
  Q_UNUSED(localSize);

  m_displayProxy->resize(fullSize);
  resetMatrix();
  fitInView(m_displayProxy, Qt::KeepAspectRatio);
}

