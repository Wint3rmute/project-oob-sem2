//
// Created by wint3rmute on 3/6/18.
//

#ifndef PROJECT_GAMEOBJECT_H
#define PROJECT_GAMEOBJECT_H


#include <SFML/Graphics.hpp>


class GameObject : public sf::Drawable {

public:
    bool wasRemoved = false;
    bool collisionsAffected = false;
    virtual void simulate() = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

};


#endif //PROJECT_GAMEOBJECT_H
