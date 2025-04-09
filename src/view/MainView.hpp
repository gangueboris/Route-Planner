#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QDesktopServices>
#include <QUrl>
#include <QCursor>

#include "model/SceneCarte.hpp"

/**
 * @class MainView
 * @brief Shows the big scene in Qt
 *
 * This class allows to draw the informations in the Big scene
 *
 * @author Boris Gangue
 * @date April 2, 2025
 */

class MainView : public QGraphicsView {
	Q_OBJECT
	public :
		MainView(SceneCarte *scene, QWidget *w, int orientation_nord = 0):QGraphicsView(scene, w), orientation_nord(orientation_nord){
			Q_UNUSED(scene);
			scale(1, -1); // inversion des y
			setMouseTracking(true);
			setViewportUpdateMode(QGraphicsView::FullViewportUpdate);// important pour la North arrow
		}
		~MainView(){}
	signals:
		void coord_viewport(QRectF);
		void position(QPointF);

	protected:
		// Gestionnaires d'évènements

		// Fit de la vue sur les limites de la scène
		void resizeEvent (QResizeEvent*) override {
			if (this->transform().m11() == 1) {
				this->fitInView(sceneRect(), Qt::KeepAspectRatio);
			}
		}

		void wheelEvent(QWheelEvent *event) override{
			int angle = event->angleDelta().y();
			qreal facteur_zoom = 1;
			if (angle > 0 ){
				facteur_zoom = 1.1;
			} else {
				facteur_zoom = 0.9;
			}

			scale ( facteur_zoom, facteur_zoom );
		}

		void paintEvent (QPaintEvent * event) override {
			// déclenché par les wheelEvents ET les scollBars
			QPolygonF poly = mapToScene(viewport()->x(),viewport()->y(),viewport()->width(),viewport()->height());
			QRectF rect_viewport = poly.boundingRect();

			emit coord_viewport(rect_viewport);
			// re-propage l'évènement
			QGraphicsView::paintEvent(event);
		}

		void mouseMoveEvent(QMouseEvent *event) override{
			QPointF pos_scene = mapToScene(event->pos());
			emit position(pos_scene);
			// re-propage l'évènement
			QGraphicsView::mouseMoveEvent(event);
		}

		void mousePressEvent(QMouseEvent *event) override{
			if(event->button() == Qt::RightButton){
				//Conversion des coord du click en celle de la scène
				QPointF pos_scene = mapToScene(event->pos());
				//Récupère les coordonées de ma ville, identifié mon item sous click
				QGraphicsItem * item = scene()->itemAt(pos_scene, transform());
				if(item){
					QString villeName = item->data(0).toString(); //récuperer le nom de la ville
					if(!villeName.isEmpty()){
						//Création du menu pour le click droit
						QMenu contextMenu;
						QAction * openWikipediaAction = new QAction ("Afficher le wikipédia de la ville", this);
						contextMenu.addAction(openWikipediaAction);
						
						//Connect pour le menu 
						connect(openWikipediaAction, &QAction::triggered, this, [villeName](){
							//Remplace le %1 par le nom de la ville
							QString url = QString("https://fr.wikipedia.org/wiki/%1").arg(villeName);
							QDesktopServices::openUrl(QUrl(url));
						});
						contextMenu.exec(QCursor::pos());
					}
				} else {
					//Si ce n'est pas un click droit l'évènement est gérer comme un click standart
					QGraphicsView::mousePressEvent(event);
				}
			}
		}

		void drawBackground( QPainter *painter, const QRectF &) override {
			//painter->save(); // pas utile
			painter->setWorldMatrixEnabled(false);// mettre en coords View (pixels)
			// Chargement image et rotation selon orientation plan
			QPixmap pixmap("../ressource/images/north.png");
			QTransform matrice;
			matrice.rotate(orientation_nord);
			QPixmap pixmap2 = pixmap.transformed(matrice);

			painter->drawPixmap(viewport()->x(),viewport()->y(),pixmap2);
			painter->setWorldMatrixEnabled(true);
			//painter->restore();  // pas utile
		}

		void drawForeground(QPainter *painter, const QRectF &) override {
			painter->setTransform(QTransform(), false); // Switch to view coordinates (pixels)
			painter->setPen(QPen(Qt::black, 2));
		
			QFont font("Arial", 12, QFont::Bold);
			painter->setFont(font);
		
			// Fixed length of scale bar (in pixels) – Adjust this value as needed
			int scaleBarLength = 50; // Assume 100 pixels = 10 km
			int x2 = this->width() - 10;  // 10px margin from right
			int y2 = this->height() - 10; // 10px margin from bottom
			int x1 = x2 - scaleBarLength;
			int y1 = y2;
			
			// Tick length (small vertical lines)
			int tickLength = 3; //qMin(scaleBarLength / 10, 5);
		
			// Draw scale bar
			painter->drawLine(x1, y1, x2, y2);
			painter->drawLine(x1, y1 - tickLength, x1, y1 + tickLength);
			painter->drawLine(x2, y2 - tickLength, x2, y2 + tickLength);
		
			// Adjust text position
			QFontMetrics metrics(font);
			int textWidth = metrics.horizontalAdvance("10 km");
			QRectF rect_texte(x1 + (scaleBarLength - textWidth) / 2, y1 - 25, textWidth, 20);
			
			// Draw text
			painter->drawText(rect_texte, Qt::AlignCenter | Qt::TextDontClip, "10 km");
		}
		
	private:
		int orientation_nord;

};

#endif
