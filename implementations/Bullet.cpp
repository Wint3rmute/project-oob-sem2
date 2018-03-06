//
// Created by wint3rmute on 3/6/18.
//

#include <cmath>
#include "../headers/Bullet.h"


Bullet :: Bullet (float pos_x, float pos_y, float rotation) : shape(BULLET_SIZE) {

    float direction = rotation * DEG_2_RAD;
    direction_x = cos(direction) * BULLET_SPEED;
    direction_y = sin(direction) * BULLET_SPEED;

    shape.setPosition(pos_x, pos_y);

}


void Bullet :: draw(sf::RenderTarget & target, sf::RenderStates states) const {

    target.draw(shape, states);

}

void Bullet :: simulate() {

    if (
            shape.getPosition().x > GAME_WINDOW_WIDTH ||
            shape.getPosition().x < 0 ||
            shape.getPosition().y > GAME_WINDOW_HEIGHT ||
            shape.getPosition().y < 0
            ) {
        GameEngine::removeObject(this);
        //delete this;
        return;
    }

    shape.move(direction_x, direction_y);

}

Bullet :: ~Bullet() {

}