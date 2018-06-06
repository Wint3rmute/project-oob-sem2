//
// Created by wint3rmute on 3/6/18.
//

/**
 * @file GameObject is the base for all objects existing inside the game.
 */

#ifndef PROJECT_GAMEOBJECT_H
#define PROJECT_GAMEOBJECT_H

#include <cmath>
#include <SFML/Graphics.hpp>
#include <cstdio>


/**
 * @brief Defines how collisions work with that object instance
 * Available collision modes:
 *  - Affected - collisions make an effect to him (example: plane is killed by a collision)
 *  - Affector - causes collisions with AFFECTED objects
 *  - Non colliding - does nothing with collisions
 *
 */

enum CollisionMode {
    AFFECTED,
    AFFECTOR,
    NON_COLLIDING
};

enum ObjectType {
    UNDEFINED,
    PLANE,
    BULLET,
    HIDEO_KOJIMA
};

/**
 * Base class for all objects used by the GameEngine
 */
class GameObject : public sf::Drawable {

public:
    /**
     * Indicates if object was removed in this frame
     */
    bool wasRemoved = false;
    CollisionMode collisionMode = NON_COLLIDING;
    ObjectType objectType = UNDEFINED;
    /**
     * Stores size of object. In fact is a radius of a circle.
     */
    float size;
    virtual void simulate() = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    /**
     * Returns position of center of the objects.
     * @return sf::Vector2f position of the object
     */
    virtual sf::Vector2f getPosition() = 0;
    virtual double getRotation() = 0;
    /**
     * @brief Creates new GameObject
     *
     * @param size ize of object's collider.
     */
    explicit GameObject(float size);

};


#endif //PROJECT_GAMEOBJECT_H
