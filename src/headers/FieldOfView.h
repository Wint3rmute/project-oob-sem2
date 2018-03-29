//
// Created by wint3rmute on 3/28/18.
//

#ifndef PROJECT_FIELDOFVIEW_H
#define PROJECT_FIELDOFVIEW_H

#include <SFML/Graphics/CircleShape.hpp>
#include "GameObject.h"
#include "Plane.h"

class FieldOfView : public GameObject {

    Plane * plane;
    int visualCellsCount;
    sf::CircleShape ** cells;
    double * distances_to_bullets;
    double * distances_to_planes;

public:
    FieldOfView(Plane * plane, int howManyCells);

    void simulate() override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::Vector2f getPosition() override;

    double getRotation() override;
};


#endif //PROJECT_FIELDOFVIEW_H
