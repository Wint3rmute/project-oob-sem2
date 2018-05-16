//
// Created by wint3rmute on 3/6/18.
//

#ifndef PROJECT_BULLET_H
#define PROJECT_BULLET_H

#include "../utils/constants.h"

#include "GameEngine.h"
#include "GameObject.h"

/**
 * @file Bullet.h
 * File containing Bullet class declaration
 */

/**
 * @brief Bullet class
 * gameObject representing a bullet - planes shoot them and get killed by them
 */
class Bullet : public GameObject {
    /**
     * SFML Shape of the bullet
     */
    sf::CircleShape shape;
    /**
     * Direction of movement on the x axis
     */
    double direction_x;
    /**
     * Direction of movement on the y axis
    */
    double direction_y;


public:
    /**
     * @brief Bullet constructor
     * Used to spawn new bullet object
     * @param pos_x First coordinate of bullet position
     * @param pos_y Second coordinate of bullet position
     * @param rotation Rotation of the bullet from horizontal orientation in degrees
     */
    Bullet (double pos_x, double pos_y, double rotation);
    /**
     * SFML Function responsible for showing shapes on screen
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    /**
     * @brief Moves bullet
     * Moves bullet along specified axis
     */
    void simulate ();
    /**
     * Returns current position of bullet
     * @return Vector with coordinates of bullet
     */
    sf::Vector2f getPosition();
    /**
     * Returns current rotation of bullet
     * @return Rotation in degrees
     */
    double getRotation();
    ~Bullet();
};


#endif //PROJECT_BULLET_H
