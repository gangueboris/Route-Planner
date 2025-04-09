#include "SceneCarte.hpp"

/**
 * @brief Draw the waypoints, contour, ville, and routes from a Carte
 * 
 * @param carte The map that contains all the information (waypoints, cities, routes, etc.)
 * Constructor of the class
 */
SceneCarte::SceneCarte(Carte& carte) {
    // Initialize carte and mainWindow
    this->carte = carte;

    // Initialize the graph with the waypoints and routes from the carte
    this->graph = Graph(this->carte.getWaypoints(), this->carte.getRoutes());

    // Draw contour (outline of the map)
    this->drawContour(carte.getContour());

    // Draw Waypoints (should be called before cities)
    this->drawWaypoint(carte.getWaypoints());

    // Draw cities
    this->drawVille(carte.getVilles());

    // Draw Routes (connections between waypoints)
    this->drawRoute(carte.getRoutes());
}

/**
 * @brief Draw the lines in Qt of a contour
 * 
 * @param Contour The outline that contains all the points to define the contour
 * @return void
 */
void SceneCarte::drawContour(Contour contour) {
    QPolygonF polygon;

    // Convert contour points from lat/lon to x/y and add them to the polygon
    for (auto& point : contour.getPoints()) {
        double x, y;
        latLonToXY(point.getLon(), point.getLat(), x, y);
        polygon << QPointF(x, y);
    }

    // Create and configure the contour item to be drawn on the scene
    QGraphicsPolygonItem* contourItem = new QGraphicsPolygonItem(polygon);
    contourItem->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    contourItem->setBrush(QBrush(Qt::green));   // Fill the contour with green color

    // Add contour item to the scene
    this->addItem(contourItem);
}

/**
 * @brief Draw roads (routes) in Qt from a vector of Route
 * 
 * @param routes Vector of roads (routes) that need to be drawn
 * @return void
 */
void SceneCarte::drawRoute(std::vector<Route> routes) {
    std::vector<Waypoint> waypoints = this->carte.getWaypoints();
    
    // Iterate through each route and draw the corresponding line between waypoints
    for (auto& route : routes) {
        // Get the start and end waypoints for the route
        Waypoint wp_start = waypoints[route.getDebut()];
        Waypoint wp_end = waypoints[route.getFin()];

        double x1, y1, x2, y2;
        latLonToXY(wp_start.getLongitude(), wp_start.getLatitude(), x1, y1);
        latLonToXY(wp_end.getLongitude(), wp_end.getLatitude(), x2, y2);

        // Create and configure the line representing the route between waypoints
        QGraphicsLineItem* routeLine = new QGraphicsLineItem(x1, y1, x2, y2);
        routeLine->setPen(QPen(Qt::black, 1));  

        // Add the route line to the scene
        this->addItem(routeLine);
    }
}

/**
 * @brief Draw cities (villes) in Qt from a vector of Ville
 * 
 * @param villes Vector of cities that need to be drawn
 * @return void
 */
void SceneCarte::drawVille(std::vector<Ville> villes) {
    for (auto& ville : villes) {
        double x, y;
        latLonToXY(ville.getLongitude(), ville.getLatitude(), x, y);

        // Create a small rectangle centered at (x, y) to represent the city
        QRectF rect(x - 2.5, y - 2.5, 5, 5);
        
        // Create and configure the city rectangle item
        QGraphicsRectItem* villeItem = new QGraphicsRectItem(rect);
        villeItem->setPen(QPen(Qt::black, 1)); // Black border
        villeItem->setBrush(QBrush(Qt::gray)); // Gray fill

        // Set a tooltip to show additional information about the city
        std::string text_tooltip = ville.getInfos();
        villeItem->setToolTip(QString::fromStdString(text_tooltip));

        // Attach the city's name for future reference (for example, on right-click)
        villeItem->setData(0, QString::fromStdString(ville.getNom()));

        // Add the city item to the scene
        this->addItem(villeItem);
    }
}

/**
 * @brief Draw waypoints in Qt from a vector of Waypoint
 * 
 * @param waypoints Vector of waypoints that need to be drawn
 * @return void
 */
void SceneCarte::drawWaypoint(std::vector<Waypoint> waypoints) {
    for(auto& waypoint : waypoints) {
        double x, y;
        latLonToXY(waypoint.getLongitude(), waypoint.getLatitude(), x, y);

        // Create a small circle centered at (x, y) to represent the waypoint
        double radius = 2;
        QRectF circleRect(x - radius, y - radius, radius * 2, radius * 2);

        // Create and configure the waypoint circle item
        QGraphicsEllipseItem* waypointItem = new QGraphicsEllipseItem(circleRect);
        waypointItem->setPen(QPen(Qt::black, 1));  // Black border
        waypointItem->setBrush(QBrush(Qt::black));  // Black fill

        // Set a tooltip to show additional information about the waypoint
        std::string text_tooltip = waypoint.getInfos();
        waypointItem->setToolTip(QString::fromStdString(text_tooltip));

        // Add the waypoint item to the scene
        this->addItem(waypointItem);
    }
}

/**
 * @brief Draw the shortest path between two cities
 * 
 * @param path Vector of integers representing the path (indices of waypoints)
 * @return void
 */
void SceneCarte::drawShortestPath(std::vector<int> path) {
    std::vector<Waypoint> waypoints = this->carte.getWaypoints();
    for(int i = 0; i < static_cast<int>(path.size())-1; ++i) {
        int index1 = path[i];
        int index2 = path[i + 1];
        Waypoint wp_start = waypoints[index1];
        Waypoint wp_dest = waypoints[index2];

        double x1, y1, x2, y2;
        latLonToXY(wp_start.getLongitude(), wp_start.getLatitude(), x1, y1);
        latLonToXY(wp_dest.getLongitude(), wp_dest.getLatitude(), x2, y2);

        // Create and configure the line representing the shortest path
        QGraphicsLineItem* pathLine = new QGraphicsLineItem(x1, y1, x2, y2);
        pathLine->setPen(QPen(Qt::red, 2));  // Red color for the shortest path

        // Add the shortest path line to the scene
        this->addItem(pathLine);
    }
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

    // Conversion into kilometers
    x /= 1000;
    y /= 1000;
}

/**
 * @brief Indicates if a waypoint is a city based on its name
 * 
 * @param wp_name Name of a waypoint
 * @return true if the waypoint is a city, false otherwise
 */
bool SceneCarte::isVille(std::string wp_name) {
    for (const auto& ville : this->carte.getVilles()) {
        if (ville.getNom() == wp_name) {
            return true; // It's a city
        }
    }
    return false; // It's not a city
}

/**
 * @brief Get the distance between the start and destination waypoints
 * 
 * @return Distance value in kilometers
 */
int SceneCarte::getDistance() {
    return this->graph.getDistance();
}

/**
 * @brief Compute and draw the shortest path from one waypoint to another
 * 
 * @param start Name of the starting waypoint
 * @param dest Name of the destination waypoint
 * @return void
 */
void SceneCarte::computeAndDrawShortestPath(const std::string& start, const std::string& dest) {
    // Validate if both start and destination are cities before calculating the path
    if(isVille(start) && isVille(dest)) {
        // Get Waypoints for the start and destination
        Waypoint wp_start(start);
        Waypoint wp_dest(dest);
        
        // Compute the shortest path using the graph
        std::vector<int> path = this->graph.getShortestPath(wp_start, wp_dest);
        this->graph.visualizePath(path);

        // Clear the previous drawing and draw the new one
        this->clear(); 

        // Redraw map elements and the shortest path
        this->drawContour(carte.getContour());
        this->drawWaypoint(carte.getWaypoints());
        this->drawVille(carte.getVilles());
        this->drawRoute(carte.getRoutes());
        this->drawShortestPath(path);
        
    } else {
        // If either start or destination is invalid, show a warning
        std::string invalid_ville = isVille(start) ? dest : start;
        emit this->signalInvalidVille(invalid_ville);
    }
}
