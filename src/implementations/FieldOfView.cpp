//
// Created by wint3rmute on 3/28/18.
//

#include <iostream>
#include "../headers/FieldOfView.h"
#include "../utils/constants.h"
#include "../headers/GameEngine.h"


FieldOfView::FieldOfView(Plane *plane, int howManyCells) : GameObject(0)  {

    this->plane = plane;
    visualCellsCount = howManyCells;

    cells = new sf::CircleShape * [visualCellsCount];

    for (int i = 0; i < visualCellsCount; ++i) {
        cells[i] = new sf::CircleShape(VISUAL_CELL_SIZE);

        cells[i]->setOrigin(2,2);
    }

    distances = new double [howManyCells];





}

void FieldOfView::simulate() {

    if(plane == NULL)
        return;

    for (int i = 0; i < visualCellsCount; ++i) {
        cells[i]->setPosition(plane->getPosition());


        cells[i]->move(
                (cos((360.0f / visualCellsCount * i + plane->getRotation()) * DEG_2_RAD)* VISUAL_CELL_DISTANCE_FROM_PLANE),
                (sin((360.0f / visualCellsCount * i + plane->getRotation()) * DEG_2_RAD)* VISUAL_CELL_DISTANCE_FROM_PLANE)
        );
    }

    double smallestDistance = 1000;
    int bestVisualCellNumber = 0;

    for (int j = 0; j < visualCellsCount; ++j) {
        distances[j] = 0.0;
    }

    for(auto gameObject : GameEngine::gameObjects) {

        if(gameObject->collisionMode == NON_COLLIDING ||gameObject == this->plane)
            continue;

        for (int i = 0; i < visualCellsCount; ++i) {

            double temporaryDistance = GameEngine::getDistance(gameObject->getPosition(), cells[i]->getPosition());

            if (temporaryDistance < smallestDistance) {
                smallestDistance = temporaryDistance;
                bestVisualCellNumber = i;
            }

        }

        distances[bestVisualCellNumber] = smallestDistance;
    }

    for (int i = 0; i < visualCellsCount; ++i) {
        cells[i]->setFillColor(sf::Color( distances[i] * 100 , 0, 0));
    }

    std::cout << distances[0] << std::endl;
}

void FieldOfView::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    for (int i = 0; i < visualCellsCount; ++i) {
        target.draw(*cells[i]);
    }
}

sf::Vector2f FieldOfView::getPosition() {
    return plane->getPosition();
}

double FieldOfView::getRotation() {
    return plane->getRotation();
}
