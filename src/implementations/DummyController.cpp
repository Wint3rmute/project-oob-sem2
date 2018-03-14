//
// Created by wint3rmute on 3/8/18.
//

#include "../headers/DummyController.h"

DummyController::DummyController(Plane *plane) : Controller(plane) {

}

void DummyController::control() {
    controlledPlane->turn(LEFT);
    controlledPlane->shoot();
}
