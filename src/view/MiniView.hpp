#ifndef MINIVIEW_H
#define MINIVIEW_H
#include <QGraphicsView>

#include "model/SceneCarte.hpp"

/**
 * @class MiniView, derived class of QGraphicsView
 * @brief Manages a collection of contacts.
 *
 * This class draws a small view on bottom of the QGroupBox
 *
 * @author Boris Gangue
 * @date April 3, 2025
 */

class MiniView : public QGraphicsView {
	Q_OBJECT
	public :
		MiniView(SceneCarte *scene, QWidget *w):QGraphicsView(scene, w){
			Q_UNUSED(scene);
			scale(1, -1);
		}
		~MiniView(){}
	public slots:
		void trace_viewport( QRectF rect_viewport){
			cadre = rect_viewport;
			viewport()->update();
		}
	private:

		void drawForeground( QPainter *painter, const QRectF &) override {
			painter->setPen(QPen(Qt::red, 0));
			painter->drawRect(cadre);
		}

		// Fit de la vue sur les limites de la scène
		void resizeEvent (QResizeEvent * ) override {
			if ( this->transform().m11() == 1){
				this->fitInView(sceneRect(), Qt::KeepAspectRatio);
			}
		}

	private:
		QRectF cadre;
};


#endif

