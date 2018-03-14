//
// Created by wint3rmute on 3/6/18.
//

#ifndef PROJECT_PLANE_H
#define PROJECT_PLANE_H


#include "GameObject.h"

class Gun;

enum DIRECTION {

    LEFT = -1,
    RIGHT = 1

};


class Plane : public GameObject {


public:
    double speed;
    sf::ConvexShape shape;
    Gun *gun;

public:
    Plane (int pos_x, int pos_y, double rotation);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void simulate ();

    void steer ();

    void turn (DIRECTION direction);
    void shoot();

    sf::Vector2f getPosition();
    double getRotation();

};



#endif //PROJECT_PLANE_H
