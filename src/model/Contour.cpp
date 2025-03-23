#include "Contour.hpp"

Contour::Contour(){

}

std::vector<Point> Contour::getPoints(){
    BDD("localhost","routeplanner","routePlanner","azerty1234");
    std::vector<Point> points;
    BDD::getPointsBDD(points);
    return points;
}

