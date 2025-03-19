#include "ScenePlan.hpp"

// Get  the tab Color
std::map<std::string, QColor> ScenePlan::tabColors = {{"rouge", Qt::red}, {"vert", Qt::green}};


ScenePlan::ScenePlan(Plan plan) : QGraphicsScene() {
   // Gets the list of Walls (murs)
   std::vector<Mur>& walls = plan.getMurs();

   for(auto &wall : walls) {
        // Get data from each walls
        QColor color = tabColors[wall.getCouleur()];
        float thinkness = wall.getEpaisseur();
        std::vector<Point>& points = wall.getPoints();

        for(int i = 0; i < (int)points.size() - 1; ++i) {
            Point p1 = points[i];
            Point p2 = points[i + 1];

            // Create the item line
            QGraphicsLineItem* line = new QGraphicsLineItem(0, 0, p2.getX() - p1.getX(), p2.getY() - p1.getY());
            line->setPos(p1.getX(), p1.getY());
            line->setPen(QPen(color, thinkness, Qt::SolidLine));

            std::string textTooltip = wall.getInfos();

            // ToolTip allow us to hovered
            line->setToolTip(QString::fromStdString(textTooltip));

            this->addItem(line); // add an item in the scene

            // Draw cercle on each erea of the map
            qreal x = points[i].getX();
            qreal y = points[i].getY();

            QGraphicsEllipseItem *origine = new QGraphicsEllipseItem(-thinkness/2, -thinkness/2, thinkness, thinkness);
            origine->setPos(x, y);  // le milieu du cercle est positionné au (0,0) de la scène
            origine->setPen(QPen(Qt::black,0,Qt::SolidLine));// épaisseur du trait 0 = 1 pixel
            origine->setBrush(QBrush(Qt::black));  // Fill the ellipse with blue color
            this->addItem(origine);
        }

        // Drw cercle for the last point
         // Draw cercle on each erea of the map
        qreal x = points[(int)points.size() - 1].getX();
        qreal y = points[(int)points.size() - 1].getY();

        QGraphicsEllipseItem *origine = new QGraphicsEllipseItem(-thinkness/2, -thinkness/2, thinkness, thinkness);
        origine->setPos(x, y);  // le milieu du cercle est positionné au (0,0) de la scène
        origine->setPen(QPen(Qt::black,0,Qt::SolidLine));// épaisseur du trait 0 = 1 pixel
        origine->setBrush(QBrush(Qt::black));  // Fill the ellipse with blue color
        this->addItem(origine);
        
   }
}