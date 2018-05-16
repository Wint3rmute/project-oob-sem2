//
// Created by wint3rmute on 3/6/18.
//

#ifndef PROJECT_CONTROLLER_H
#define PROJECT_CONTROLLER_H


#include "Plane.h"
#include "FieldOfView.h"
class FieldOfView;
/**
 * @file Controller.h
 * File contains Controller class declaration
 */

/**
 * @brief Controller base
 * Base class for classes controlling planes:
 *
 * @see KeyboardController, @see NeuralController
 */
class Controller {
protected:
    /**
     * Plane that this controller controlls
     */
    Plane * controlledPlane;

public:
    /**
     * Indicates if plane was already removed in this frame
     */
    bool wasRemoved = false;
    FieldOfView * fieldOfView;
    explicit Controller(Plane * plane);
    /**
     * Virtual method to that implements actual plane controlling
     */
    virtual void control() = 0;
};


#endif //PROJECT_CONTROLLER_H
