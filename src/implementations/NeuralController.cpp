//
// Created by wint3rmute on 4/1/18.
//

#include "../headers/NeuralController.h"

NeuralController::NeuralController(NetworkParams *params, Plane *plane, FieldOfView * fieldOfView)
        : NeuralNet(params), Controller(plane) {

    this->fieldOfView = fieldOfView;
    inputs = new double[VISUAL_CELLS_COUNT * 2];
}

void NeuralController::control() {

    int currentInputsIndex;

    for (currentInputsIndex = 0; currentInputsIndex < VISUAL_CELLS_COUNT; ++currentInputsIndex) {
        inputs[currentInputsIndex] = fieldOfView->distances_to_planes[currentInputsIndex];
    }

    for (int z = 0; z < VISUAL_CELLS_COUNT; ++z) {
        inputs[currentInputsIndex]= fieldOfView->distances_to_bullets[z];

        currentInputsIndex++;
    }

    outputs = process(inputs);

    if(outputs[0] > 0.5){
        controlledPlane->turn(LEFT);
    }else{
        controlledPlane->turn(RIGHT);
    }

    if(outputs[1] > 0.5){
        controlledPlane->shoot();
    }

}

NeuralController::~NeuralController() {
    delete inputs;
}

