#ifndef SCENECARTE_H
#define SCENECARTE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <QColor>
#include <map>
#include<iostream>
#include <cmath>

#include "Graph.hpp"
#include "Carte.hpp" 


class SceneCarte : public QGraphicsScene {
Q_OBJECT
public :
       SceneCarte(Carte& carte);
       ~SceneCarte(){}

       void drawContour(Contour contour);
       void drawRoute(std::vector<Route> routes);
       void drawWaypoint(std::vector<Waypoint> waypoints);
       void drawVille(std::vector<Ville> villes);
       void drawShortestPath(std::vector<int> path);
       int getDistance();
       void computeAndDrawShortestPath(const std::string& start, const std::string& dest);
       
private:
       static std::map<std::string, QColor> tabColors;
       void latLonToXY(float lon, float lat, double &x, double &y);
       bool isVille(std::string wp_name);
       Graph graph;
       Carte carte;
};

#endif