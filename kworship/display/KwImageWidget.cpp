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
KwImageWidget::KwImageWidget(const QPixmap& pixmap, bool stretch, bool keepAspect)
: QWidget()
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
  if (!m_pixmap.isNull())
  {
    QPainter painter(this);
    painter.setClipRegion(e->region());
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
  }
}

