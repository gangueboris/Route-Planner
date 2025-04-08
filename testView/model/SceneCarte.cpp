#include "SceneCarte.hpp"

//std::map<std::string, QColor> SceneCarte::tabColors = {{"black", Qt::black}, {"green", Qt::green}};

SceneCarte::SceneCarte(Carte& carte) {
    // Init carte and mainWindow
    this->carte = carte;
    
    this->graph = Graph(this->carte.getWaypoints(), 70);
                                                                                                                                            
   // Draw contour
   this->drawContour(carte.getContour());

   // Draw Waypoints  Must be called first before ville
   this->drawWaypoint(carte.getWaypoints());

   // Draw ville 
   this->drawVille(carte.getVilles());

   // Draw Routes
   this->drawRoute(carte.getRoutes());

   // Compute and draw graph
   //std::cout << this->start << "  " << this->dest << '\n';
   
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

void SceneCarte::drawRoute(std::vector<Route> routes) {
    std::vector<Waypoint> waypoints = this->carte.getWaypoints();
    
    for (auto& route : routes) {
        // Get waypoints
        Waypoint wp_start = waypoints[route.getDebut()];
        Waypoint wp_end = waypoints[route.getFin()];

        double x1, y1, x2, y2;
        latLonToXY(wp_start.getLongitude(), wp_start.getLatitude(), x1, y1);
        latLonToXY(wp_end.getLongitude(), wp_end.getLatitude(), x2, y2);

        // Create and configure the line item
        QGraphicsLineItem* routeLine = new QGraphicsLineItem(x1, y1, x2, y2);
        routeLine->setPen(QPen(Qt::black, 1));  

        // Add to the scene
        this->addItem(routeLine);
    }
}


void SceneCarte::drawVille(std::vector<Ville> villes) {
    for (auto& ville : villes) {
        double x, y;
        latLonToXY(ville.getLongitude(), ville.getLatitude(), x, y);

        // Create a small rectangle centered at (x, y)
        QRectF rect(x - 2.5, y - 2.5, 5, 5);
        
        // Create and configure the rectangle item
        QGraphicsRectItem* villeItem = new QGraphicsRectItem(rect);
        villeItem->setPen(QPen(Qt::black, 1)); // Black border
        villeItem->setBrush(QBrush(Qt::gray)); // Gray fill

        // Handle the tooltip
        std::string text_tooltip = ville.getInfos();
        villeItem->setToolTip(QString::fromStdString(text_tooltip));

        // Add to the scene
        this->addItem(villeItem);
    }
}

void SceneCarte::drawWaypoint(std::vector<Waypoint> waypoints) {
    for(auto& waypoint : waypoints) {
        double x, y;
        latLonToXY(waypoint.getLongitude(), waypoint.getLatitude(), x, y);

        // Create a small circle centered at (x, y)
        double radius = 2;
        QRectF circleRect(x - radius, y - radius, radius * 2, radius * 2);

        // Create and configure the circle item
        QGraphicsEllipseItem* waypointItem = new QGraphicsEllipseItem(circleRect);
        waypointItem->setPen(QPen(Qt::black, 1));  // Black border
        waypointItem->setBrush(QBrush(Qt::black));  // Gray fill

        // Handle the tooltip
        std::string text_tooltip = waypoint.getInfos();
        waypointItem->setToolTip(QString::fromStdString(text_tooltip));

        // Add to the scene
        this->addItem(waypointItem);
    }
}



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

        // Create and configure the line item
        QGraphicsLineItem* pathLine = new QGraphicsLineItem(x1, y1, x2, y2);
        pathLine->setPen(QPen(Qt::red, 2));  

        // Add to the scene
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

    // conversion into km
    x /=  1000;
    y /= 1000;
}

bool SceneCarte::isVille(std::string wp_name) {
    for (const auto& ville : this->carte.getVilles()) {
        if (ville.getNom() == wp_name) {
            return true; 
        }
    }
    return false;
}


int SceneCarte::getDistance() {
    std::vector<Waypoint> waypoints = this->carte.getWaypoints();
    int index1 = this->graph.findWaypointIndex(Waypoint(this->start));
    int index2 =  this->graph.findWaypointIndex(Waypoint(this->dest));

    return this->graph.getDistance(waypoints[index1], waypoints[index2]);
}

void SceneCarte::computeAndDrawShortestPath(const std::string& start, const std::string& dest) {
    /*
     1. Get waypoints from name
     2. call the shortest path
     3. Implement the drawShortestPath and call it
    */
   
    // Validate if start and dest are villes before...
    if(isVille(start) && isVille(dest)) {
        // Init start and dest
        this->start = start;
        this->dest = dest;
    
        // Get Waypoints
        Waypoint wp_start(start);
        Waypoint wp_dest(dest);
        
        // Compute the shortest path
        std::vector<int> path = this->graph.getShortestPath(wp_start, wp_dest);
        this->graph.visualizePath(path);

        // Clear the previous drawing and draw the new line
        this->clear(); 

        // Draw contour
        this->drawContour(carte.getContour());

        // Draw Waypoints  Must be called first before ville
        this->drawWaypoint(carte.getWaypoints());

        // Draw ville 
        this->drawVille(carte.getVilles());

        // Draw Routes
        this->drawRoute(carte.getRoutes());
        
        // Draw ShortestPath
        this->drawShortestPath(path);
        
    } else {
        std::cout << "City not valid !! \n";
    }
}

