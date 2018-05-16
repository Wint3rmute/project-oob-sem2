//
// Created by wint3rmute on 3/6/18.
//

#ifndef PROJECT_PLANE_H
#define PROJECT_PLANE_H


#include "GameObject.h"

/**
 * @file Plane.h
 *
 * @contains all code needed for the Plane object to function
 */

class Controller;
class Gun;
class Boost;

/**
 * @brief LEFT and RIGHT - to make functions for plane steering more readable
 */
enum DIRECTION {

    LEFT = -1,
    RIGHT = 1

};

/**
 * @brief Plane object, can be controlled by a controller object:
 * that could be a player or a neural network
 *
 * it uses some simple physics to make gameplay a little more challenging
 */
class Plane : public GameObject {

    /**
     * @brief Counter for the amount of planes currently in-game
     *
     * used in neural network training to determine whether new networks should be mutated and join the game
     */
    static int howManyPlanes;

    /**
     * @brief polygon - shape of the plane
     */
    sf::ConvexShape shape;
    double speed;
    Gun *gun;
    Boost *booster;
    Controller * controller;

public:
    /**
     * @brief Creates a plane object ready to be added into GameEngine scene
     * @param pos_x position X of the plane
     * @param pos_y position Y of the plane
     * @param rotation rotation, in degrees
     */
    Plane (int pos_x, int pos_y, double rotation);

    /**
     * @brief set the controller the plane is being controller by
     * @param controller @see Controller
     */
    void setController(Controller * controller);
    Controller * getController();
    void setSpeed(double speed);

    /**
     * @brief Makes the object drawable in the game window.
     *
     * Inherited from Drawable
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void simulate ();

    /**
     * @name Methods for controlling the plane
     *
     * Allow the plane to turn, boost and shoot
     * */
    ///@{
    /**
     * Turns the plane in a specified direction
     * @param direction the DIRECTION enum
     */
    void turn (DIRECTION direction);
    void shoot();
    void boost();
    ///@}

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
