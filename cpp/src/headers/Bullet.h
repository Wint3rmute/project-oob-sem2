//
// Created by wint3rmute on 3/6/18.
//

#ifndef PROJECT_BULLET_H
#define PROJECT_BULLET_H

#include "../utils/constants.h"

#include "GameEngine.h"
#include "GameObject.h"

/*
 * gameObject representing a bullet - planes shoot them and get killed by them
 */
class Bullet : public GameObject {

    sf::CircleShape shape;
    double direction_x; // will be set only once, not per each frame.. so we save it as the class property
    double direction_y;


public:
    Bullet (double pos_x, double pos_y, double rotation);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void simulate ();

    sf::Vector2f getPosition();
    double getRotation();

    ~Bullet();
};


#endif //PROJECT_BULLET_H
