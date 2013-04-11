/* Nokia License */
/* TI License */

#ifndef _QGRAPHICSSVGNATIVEITEM_H
#define _QGRAPHICSSVGNATIVEITEM_H

//#include <QtGui/qgraphicsitem.h>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsWidget>
#include <qsvgwidget.h>

/*
 * This class eliminates unneeded QImage to QPixmap conversions
 * that are used by default in SVG + Graphicsview implementation in 
 * Qt, without any loss of visual quality. The original SVG
 * renderer is still used to render the image at high resolution.
 * Improves CPU utilisation.
 * Usage:
 *   graphicsItem = new QGraphicsSvgNativeItem("mysvgfile.svg");
 * TODO: clarify complete paths
 */


class QGraphicsSvgNativeItem : public QGraphicsPixmapItem
{
public: 
  QGraphicsSvgNativeItem ( const QString & file, QSize targetSize = QSize(0,0), QGraphicsItem * parent = 0 )
  : QGraphicsPixmapItem(parent)
  {
    currSvgWidget = 0;
    currPixmap = 0;
    currSvgWidget = new QSvgWidget(file);
	if(targetSize.width() == 0) targetSize = currSvgWidget->sizeHint();
    if(currSvgWidget)
    {
      currPixmap = new QPixmap(targetSize); //currSvgWidget->sizeHint());
      if(currPixmap)
      {
        currPixmap->fill(Qt::transparent);
		currSvgWidget->resize(targetSize);
        currSvgWidget->render(currPixmap, QPoint(), QRegion(), QWidget::DrawChildren);
        setPixmap(*currPixmap);
        setTransformationMode(Qt::SmoothTransformation);
      }
    }
  };    
 ~QGraphicsSvgNativeItem ()
 {
   if(currPixmap)
      delete currPixmap;
    if(currSvgWidget)
      delete currSvgWidget; 
 };   

    enum { Type = UserType + 555 };
    int type() const {return Type;};
private:
    QPixmap* currPixmap;
    QSvgWidget* currSvgWidget;


};			

#endif
