//
// Created by wint3rmute on 3/28/18.
//

#include <iostream>
#include "../headers/FieldOfView.h"


FieldOfView::FieldOfView(Plane *plane, int howManyCells) : GameObject(0)  {

    this->plane = plane;
    visualCellsCount = howManyCells;
    objectType = HIDEO_KOJIMA;

    cells = new sf::CircleShape * [visualCellsCount];

    for (int i = 0; i < visualCellsCount; ++i) {
        cells[i] = new sf::CircleShape(VISUAL_CELL_SIZE);

        cells[i]->setOrigin(2,2);
    }

    distances_to_bullets = new double [howManyCells];
    distances_to_planes = new double [howManyCells];


}

void FieldOfView::simulate() {

    if(plane->wasRemoved) //
    {
        GameEngine::removeObject(this);
        return;
    }


    for (int i = 0; i < visualCellsCount; ++i) {
        cells[i]->setPosition(plane->getPosition());


        cells[i]->move(
                (cos((360.0f / visualCellsCount * i + plane->getRotation()) * DEG_2_RAD)* VISUAL_CELL_DISTANCE_FROM_PLANE),
                (sin((360.0f / visualCellsCount * i + plane->getRotation()) * DEG_2_RAD)* VISUAL_CELL_DISTANCE_FROM_PLANE)
        );
    }


    double smallestDistanceBullet = 100000.0,
            smallestDistancePlane = 100000.0;

    int bestVisualCellNumberBullet = -1,
            bestVisualCellNumberPlane = -1;

    for (int j = 0; j < visualCellsCount; ++j) {
        distances_to_bullets[j] = 0.0;
        distances_to_planes[j] = 0.0;
    }


    for(auto gameObject : GameEngine::gameObjects) {

        if(gameObject->collisionMode == NON_COLLIDING or gameObject == this->plane)
            continue;

        for (int i = 0; i < visualCellsCount; ++i) {

            double temporaryDistance = GameEngine::getDistance(gameObject->getPosition(), cells[i]->getPosition());

            if(gameObject->collisionMode == AFFECTOR) { //if we have a bullet TODO: this if fires too many times, this could be checked before the loop
                if (temporaryDistance < smallestDistanceBullet) {
                    smallestDistanceBullet = temporaryDistance;
                    bestVisualCellNumberBullet = i;
                }

            } else {

                if (temporaryDistance < smallestDistancePlane) { //if we have a plane
                    smallestDistancePlane = temporaryDistance;
                    bestVisualCellNumberPlane = i;
                }
            }
        }

        if(bestVisualCellNumberPlane != -1)
            distances_to_planes[bestVisualCellNumberPlane] = smallestDistancePlane;


        if(bestVisualCellNumberBullet != -1)
            distances_to_bullets[bestVisualCellNumberBullet] = smallestDistanceBullet;
    }

    for (int i = 0; i < visualCellsCount; ++i) {
        cells[i]->setFillColor(sf::Color( 56 +distances_to_planes[i] * 100 , 56 + distances_to_bullets[i] * 100, 56));
        //std::cout << distances_to_planes[i] << std::endl;
    }




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

FieldOfView::~FieldOfView() {


    for (int i = 0; i < visualCellsCount; ++i) {
        delete cells[i];

        delete cells;

        delete distances_to_bullets;
        return;

        delete distances_to_planes;
}

}
