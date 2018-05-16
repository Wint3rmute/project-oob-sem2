//
// Created by wint3rmute on 3/6/18.
//

#ifndef PROJECT_PLANE_H
#define PROJECT_PLANE_H


#include "GameObject.h"


class Controller;
class Gun;
class Boost;

enum DIRECTION {

    LEFT = -1,
    RIGHT = 1

};

/**
 * Plane object, can be controlled by a controller object:
 * that could be a player or a neural network
 *
 * it uses some simple physics to make gameplay a little more challenging
 */
class Plane : public GameObject {

    static int howManyPlanes;
    sf::ConvexShape shape;
    double speed;
    Gun *gun;
    Boost *booster;
    Controller * controller;

public:
    /**
     * for creating a plane object ready to be added into GameEngine scene
     */
    Plane (int pos_x, int pos_y, double rotation);

    void setController(Controller * controller);
    Controller * getController();
    void setSpeed(double speed);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void simulate ();

    /**
     * an interface to control the plane
     *
     * allows for turning, shooting and boosting
     */
    void turn (DIRECTION direction);
    void shoot();
    void boost();


    sf::Vector2f getPosition();
    double getRotation();
    double getSpeed();

    /**
     * return the static variable showing how many planes exist currently
     *
     * used for network training - monitoring the number of networks currently on scene
     */
    static int howManyPlanesAreThere();

    int operator+(DIRECTION direcion);

    ~Plane();

};



#endif //PROJECT_PLANE_H
