//
// Created by wint3rmute on 3/6/18.
//

#ifndef PROJECT_PLANE_H
#define PROJECT_PLANE_H


#include "GameObject.h"

class Controller;
class Gun;

enum DIRECTION {

    LEFT = -1,
    RIGHT = 1

};


class Plane : public GameObject {

    static int howManyPlanes;
    sf::ConvexShape shape;
    double speed;
    Gun *gun;
    Controller * controller;

public:
    Plane (int pos_x, int pos_y, double rotation);

    void setController(Controller * controller);
    Controller * getController();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void simulate ();

    void turn (DIRECTION direction);
    void shoot();

    sf::Vector2f getPosition();
    double getRotation();

    ~Plane();

};



#endif //PROJECT_PLANE_H
