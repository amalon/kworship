#ifndef _KwImageWidget_h_
#define _KwImageWidget_h_

/**
 * @file KwImageWidget.h
 * @brief Background image widget.
 * @author James Hogan <james@albanarts.com>
 */

#include <QWidget>

/// Background image widget.
class KwImageWidget : public QWidget
{
  public:

    /*
     * Constructors + destructors
     */

    /// Primary constructor.
    KwImageWidget(const QPixmap& pixmap, bool stretch, bool keepAspect);

    /// Destructor.
    virtual ~KwImageWidget();

  protected:

    /*
     * Events
     */

    /// Repaint evemt.
    void paintEvent(QPaintEvent* e);

  private:

    /*
     * Variables
     */

    /// Pixmap image.
    QPixmap m_pixmap;

    /// Whether to stretch the image to fit the screen.
    bool m_stretch;

    /// Whether to keep the aspect ratio of the image.
    bool m_keepAspect;
};

#endif // _KwImageWidget_h_

