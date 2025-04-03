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
void SceneCarte::drawWaypoint(std::vector<Waypoint> waypoints) {

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