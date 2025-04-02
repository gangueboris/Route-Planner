#ifndef SCENECARTE_H
#define SCENECARTE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>
#include <QColor>
#include <map>
#include<iostream>


#include "Graph.hpp"
#include "Carte.hpp"

class SceneCarte : public QGraphicsScene {
	Q_OBJECT
	public :
		SceneCarte(Carte & carte);
       ~SceneCarte(){}

       void drawContour(Contour contour);
       void drawRoute(Route route);
       void drawWaypoint(std::vector<Waypoint> waypoints);
       void drawShortestPath(std::vector<Route> routes);
		
	private:
		static std::map<std::string, QColor> tabColors;
};

#endif