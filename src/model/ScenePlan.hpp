#ifndef SCENE_PLAN_H
#define SCENE_PLAN_H


#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <map>
#include "Plan.h"

class ScenePlan: public QGraphicsScene {
    public:
       // Constructor
       ScenePlan(Plan plan);

        // Destructor
        virtual ~ScenePlan(){}
        
    
    private:
       static std::map<std::string, QColor> tabColors;
};
#endif