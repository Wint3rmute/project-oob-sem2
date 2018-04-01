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
        inputs[currentInputsIndex] = fieldOfView->distances_to_planes[currentInputsIndex] / sqrt(GAME_WINDOW_HEIGHT * GAME_WINDOW_HEIGHT + GAME_WINDOW_WIDTH + GAME_WINDOW_WIDTH);
    }

    for (int z = 0; z < VISUAL_CELLS_COUNT; ++z) {
        inputs[currentInputsIndex]= fieldOfView->distances_to_bullets[z] / sqrt(GAME_WINDOW_HEIGHT * GAME_WINDOW_HEIGHT + GAME_WINDOW_WIDTH + GAME_WINDOW_WIDTH);

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

NeuralController::NeuralController(NeuralController *parent, Plane *plane, FieldOfView *fieldOfView) : NeuralNet(parent), Controller(plane) {
    this->fieldOfView = fieldOfView;
    inputs = new double[VISUAL_CELLS_COUNT * 2];
}

void NeuralController::randomize(double percent) {
    randomizeByPercent(percent);
}

