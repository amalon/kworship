#ifndef _KwLocalDisplayPreview_h_
#define _KwLocalDisplayPreview_h_

/**
 * @file KwLocalDisplayPreview.h
 * @brief Wrapper around KwLocalDisplay to allow scaling preview.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractDisplay.h"
#include "KwLocalDisplay.h"

#include <QGraphicsView>

/// Wrapper around KwLocalDisplay to allow scaling preview.
class KwLocalDisplayPreview : public QGraphicsView, public KwAbstractDisplay
{
    Q_OBJECT
  public:

    /*
     * Constructors + destructors
     */

    /// Primary constructor.
    KwLocalDisplayPreview(QWidget* parent = 0);

    /// Destructor.
    virtual ~KwLocalDisplayPreview();

    /*
     * Public methods
     */

    /// Set whether this preview is the primary display.
    /**
     * This makes the size of the display match the size of this preview.
     */
    void setPrimary(bool newIsPrimary = true);

  protected:

    /*
     * Main interface events for extension
     */

    /// @copydoc KwAbstractDisplay::setDisplayResolutionEvent(QSize)
    virtual void setDisplayResolutionEvent(QSize size);

    /// @copydoc KwAbstractDisplay::clearLayersEvent()
    virtual void clearLayersEvent();

    /// @copydoc KwAbstractDisplay::setLayerEvent(unsigned int, const KwAbstractLayer*, bool)
    virtual void setLayerEvent(unsigned int index, const KwAbstractLayer* layer, bool insert);

    /// @copydoc KwAbstractDisplay::removeLayerEvent(unsigned int)
    virtual void removeLayerEvent(unsigned int index);


    /*
     * QT Events
     */

    /// @copydoc QWidget::resizeEvent(QResizeEvent*)
    void resizeEvent(QResizeEvent*);

  private:

    /*
     * Variables
     */

    /// Is this preview the primary display?
    bool m_isPrimary;

    /// Graphics scene.
    QGraphicsScene* m_scene;

    /// The actual display.
    KwLocalDisplay* m_display;

    /// The proxy object for the display.
    QGraphicsProxyWidget* m_displayProxy;

    /*
     * Private methods
     */

    /// Resize contents.
    void resizeContents(QSize fullSize, QSize localSize);
};

#endif // _KwLocalDisplayPreview_h_

