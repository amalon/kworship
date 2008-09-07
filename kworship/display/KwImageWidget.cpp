/**
 * @file KwImageWidget.cpp
 * @brief Background image widget.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwImageWidget.h"

#include <QPainter>
#include <QPaintEvent>

/*
 * Constructors + destructors
 */

/// Primary constructor.
KwImageWidget::KwImageWidget(QBrush brush)
: QWidget()
, m_brush(brush)
, m_pixmap()
, m_stretch(false)
, m_keepAspect(false)
{
}

/// Primary constructor.
KwImageWidget::KwImageWidget(const QPixmap& pixmap, bool stretch, bool keepAspect)
: QWidget()
, m_brush()
, m_pixmap(pixmap)
, m_stretch(stretch)
, m_keepAspect(keepAspect)
{
}

/// Primary constructor.
KwImageWidget::KwImageWidget(QBrush brush, const QPixmap& pixmap, bool stretch, bool keepAspect)
: QWidget()
, m_brush(brush)
, m_pixmap(pixmap)
, m_stretch(stretch)
, m_keepAspect(keepAspect)
{
}

/// Destructor.
KwImageWidget::~KwImageWidget()
{
}


/*
 * Events
 */

/// Repaint evemt.
void KwImageWidget::paintEvent(QPaintEvent* e)
{
  QPainter painter(this);
  painter.setClipRegion(e->region());

  // Image
  if (!m_pixmap.isNull())
  {
    QSize sizeOnScreen(m_pixmap.size());
    QRect fragment(0, 0, m_pixmap.width(), m_pixmap.height());

    if (m_stretch)
    {
      sizeOnScreen = size();
      if (m_keepAspect)
      {
        if (width() * m_pixmap.height() > m_pixmap.width() * height())
        {
          sizeOnScreen.setWidth(sizeOnScreen.height() * m_pixmap.width() / m_pixmap.height());
        }
        else
        {
          sizeOnScreen.setHeight(sizeOnScreen.width() * m_pixmap.height() / m_pixmap.width());
        }
      }
    }
  
    QRect placement(0, 0, sizeOnScreen.width(), sizeOnScreen.height());
    placement.moveCenter(QPoint(width()>>1, height()>>1));
    painter.drawPixmap(placement, m_pixmap, fragment);

    /// @todo Brush the background
  }
  else
  {
    // Just brush it
    painter.fillRect(e->region().boundingRect(), m_brush);
  }
}

