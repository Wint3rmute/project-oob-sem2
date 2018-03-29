//
// Created by wint3rmute on 3/6/18.
//

#include <cmath>
#include <iostream>
#include "../headers/Plane.h"
#include "../utils/constants.h"
#include "../headers/Gun.h"

using namespace std;
class Gun;

int Plane::howManyPlanes;

Plane::Plane (int pos_x, int pos_y, double rotation) : GameObject(PLANE_COLLIDER_SIZE) {

    howManyPlanes++;

    collisionMode = AFFECTED;

    speed = PLANE_SPEED;
    gun = new Gun();
    // resize shape to 5 points
   shape.setPointCount(4);

    // define the shape points
    shape.setPoint(0, sf::Vector2f(12, 14));
    shape.setPoint(1, sf::Vector2f(0, 0));
    shape.setPoint(2, sf::Vector2f(34, 14));
    shape.setPoint(3, sf::Vector2f(0, 28));
    //shape.setPoint(4, sf::Vector2f(0, 14));

    sf::FloatRect boundingBox = shape.getGlobalBounds();


    shape.setPosition(pos_x, pos_y);
    shape.setRotation(rotation);
    shape.setOrigin(boundingBox.width / 2.0 , boundingBox.height / 2.0 );

}


void Plane :: draw(sf::RenderTarget& target, sf::RenderStates states) const {

    sf::CircleShape s;
    s.setRadius(1);
    s.setFillColor(sf::Color::Red);


    s.setPosition(shape.getPosition());
    target.draw(shape, states);
    target.draw(s, states);
}

void Plane :: simulate() {


    double angle_rad = shape.getRotation() * DEG_2_RAD;

    shape.move(cos(angle_rad) * speed , sin(angle_rad) * speed);

    speed += sin(angle_rad) * ACCELERATION_MULTIPLIER;

    if ( shape.getPosition().y <= -TELEPORTATION_TRIGGER_OFFSET)
        shape.move(0, GAME_WINDOW_HEIGHT + TELEPORTATION_TRIGGER_OFFSET);

    if ( shape.getPosition().y >= GAME_WINDOW_HEIGHT + TELEPORTATION_TRIGGER_OFFSET)
        shape.move(0, -GAME_WINDOW_HEIGHT - TELEPORTATION_TRIGGER_OFFSET);

    if ( shape.getPosition().x <= -TELEPORTATION_TRIGGER_OFFSET )
        shape.move(GAME_WINDOW_WIDTH + TELEPORTATION_TRIGGER_OFFSET,0);

    if ( shape.getPosition().x >= GAME_WINDOW_WIDTH + TELEPORTATION_TRIGGER_OFFSET)
        shape.move(-GAME_WINDOW_WIDTH - TELEPORTATION_TRIGGER_OFFSET, 0) ;


    if (speed > MAX_SPEED)
        speed = MAX_SPEED;

    else if (speed < MIN_SPEED)
        speed = MIN_SPEED;


}


void Plane :: turn(DIRECTION direction) {
    shape.rotate(direction * ROTATION_SPEED * speed);
}
void Plane :: shoot() {
    gun->activate(*this);
}

sf::Vector2f Plane :: getPosition() {
    return shape.getPosition();
}

double Plane :: getRotation() {
    return shape.getRotation();
}

void Plane::setController(Controller *controller) {
    this->controller = controller;
}

Plane::~Plane() {
    delete gun;
    howManyPlanes--;
    cout << howManyPlanes << endl;
}

Controller *Plane::getController() {
    return controller;
}
