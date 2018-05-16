//
// Created by wint3rmute on 3/28/18.
//

#ifndef PROJECT_FIELDOFVIEW_H
#define PROJECT_FIELDOFVIEW_H

#include <SFML/Graphics/CircleShape.hpp>
#include "GameObject.h"
#include "Plane.h"
#include "../headers/FieldOfView.h"
#include "../utils/constants.h"
#include "../headers/GameEngine.h"
/**
 * @file FieldOfView.h
 * File contains field of view declaration and sight cells definition.
 */

/**
 * @brief A component that serves as the sense of sight for the AI plane
 * Creates sight cells around the plane. Distance between them and objects in game
 * is calculated to determine their direction in reference to plane.
 * Info from this class is delivered as info for bots.
 */
class FieldOfView : public GameObject {

    /**
     * Plane to witch field belongs
     */
    Plane * plane;

    /**
     * How many visual cells do we have
     * that directly affects the accuracy of the bot
     */
    int visualCellsCount;

    /**
     * CircleShapes are used for visualisation of the bots input data
     */
    sf::CircleShape ** cells;


public:

    /**
     * Those two arrays are the inputs for the bot
     *
     * They are public, because this is the simplest way to deal with them
     */
    double * distances_to_bullets;
    double * distances_to_planes;

    FieldOfView(Plane * plane, int howManyCells);

    /**
     * Methods required from the base object
     */
    void simulate() override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    sf::Vector2f getPosition() override;
    double getRotation() override;

    ~FieldOfView();
};


#endif //PROJECT_FIELDOFVIEW_H