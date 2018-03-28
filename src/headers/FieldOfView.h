//
// Created by wint3rmute on 3/28/18.
//

#ifndef PROJECT_FIELDOFVIEW_H
#define PROJECT_FIELDOFVIEW_H

#include <SFML/Graphics/CircleShape.hpp>
#include "GameObject.h"

class Plane;

class FieldOfView : public GameObject {

    Plane * plane;
    int visualCells;
    sf::CircleShape * cells;

public:
    FieldOfView(Plane * plane);



};


#endif //PROJECT_FIELDOFVIEW_H
