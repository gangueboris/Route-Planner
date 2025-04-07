#include "SceneCarte.hpp"

//std::map<std::string, QColor> SceneCarte::tabColors = {{"black", Qt::black}, {"green", Qt::green}};

SceneCarte::SceneCarte(Carte& carte) {
   // Draw contour
   this->drawContour(carte.getContour());
}
      
void SceneCarte::drawContour(Contour contour) {
    QPolygonF polygon;

    for (auto& point : contour.getPoints()) {
        double x, y;
        latLonToXY(point.getLon(), point.getLat(), x, y);
        polygon << QPointF(x, y);
    }

    // Create and configure the contour item
    QGraphicsPolygonItem* contourItem = new QGraphicsPolygonItem(polygon);
    contourItem->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    contourItem->setBrush(QBrush(Qt::green));   // Fill with green
   

    // Add contour to the scene
    this->addItem(contourItem); 
}
void SceneCarte::drawRoute(Route route) {

}

void SceneCarte::drawVille(std::vector<Ville> villes) {
    for (auto& ville : villes) {
        double x, y;
        latLonToXY(ville.getLon(), ville.getLat(), x, y);
        

        // Create a small rectangle centered at (x, y)
        QRectF rect(x - 2.5, y - 2.5, 5, 5);
        
        // Create and configure the rectangle item
        QGraphicsRectItem* villeItem = new QGraphicsRectItem(rect);
        villeItem->setPen(QPen(Qt::black, 1)); // Black border
        villeItem->setBrush(QBrush(Qt::gray)); // Gray fill

        // Add to the scene
        this->addItem(villeItem);
    }
}

void SceneCarte::drawWaypoint(std::vector<Waypoint> waypoints) {
    /*
        As arguments, I will get vector<Waypoint> and vector<Ville>.
        - Iterate through vector<Ville> and draw small square. 
        - To get the get the coords, I will use the getWaypoint by name. And in the tooltip, fill with the get of will. 
        - for every ville, I will change the isVille in the Waypoint vector to true. 
        - I have to iterate in vector<Waypoint> check if it's not Ville  and draw waypoint.
    */
    


}
void SceneCarte::drawShortestPath(std::vector<Route> routes) {
    
}

/**
 * @brief Converts geographic coordinates (longitude, latitude) to Cartesian (x, y) using the Mercator projection.
 * 
 * @param lon Longitude in degrees.
 * @param lat Latitude in degrees.
 * @param x Reference to store the computed x-coordinate.
 * @param y Reference to store the computed y-coordinate.
 */
void SceneCarte::latLonToXY(float lon, float lat, double &x, double &y) {
    const double EARTH_RADIUS = 6378137.0; // Earth's radius in meters

    // Convert degrees to radians
    double lonRad = lon * M_PI / 180.0;
    double latRad = lat * M_PI / 180.0;

    // Calculate x and y using Mercator projection
    x = EARTH_RADIUS * lonRad ;
    y = EARTH_RADIUS * log(tan(M_PI / 4.0 + latRad / 2.0));

    // conversion into km
    x /=  1000;
    y /= 1000;
}

int SceneCarte::getDistance() {
    return 0;
}