//
// Created by wint3rmute on 4/1/18.
//

#include <iostream>
#include "../headers/NeuralController.h"

NeuralController::NeuralController(NetworkParams *params, Plane *plane, FieldOfView * fieldOfView)
        : NeuralNet(params), Controller(plane) {

    this->fieldOfView = fieldOfView;
    inputs = new double[VISUAL_CELLS_COUNT * 2];
}

NeuralController::NeuralController(NeuralController *parent, Plane *plane, FieldOfView *fieldOfView) : NeuralNet(parent), Controller(plane) {
    this->fieldOfView = fieldOfView;
    inputs = new double[VISUAL_CELLS_COUNT * 2];
}

void NeuralController::control() {

    int currentInputsIndex;

    /**
     * the part
     *
     *  / sqrt(GAME_WINDOW_HEIGHT * GAME_WINDOW_HEIGHT + GAME_WINDOW_WIDTH + GAME_WINDOW_WIDTH)
     *
     *  is data normalisation, it gives the input a value between -1 and 1
     *
     */
    for (currentInputsIndex = 0; currentInputsIndex < VISUAL_CELLS_COUNT; ++currentInputsIndex) {
        inputs[currentInputsIndex] = fieldOfView->distances_to_planes[currentInputsIndex] / sqrt(GAME_WINDOW_HEIGHT * GAME_WINDOW_HEIGHT + GAME_WINDOW_WIDTH + GAME_WINDOW_WIDTH);
    }

    for (int z = 0; z < VISUAL_CELLS_COUNT; ++z) {
        inputs[currentInputsIndex]= fieldOfView->distances_to_bullets[z] / sqrt(GAME_WINDOW_HEIGHT * GAME_WINDOW_HEIGHT + GAME_WINDOW_WIDTH + GAME_WINDOW_WIDTH);

        currentInputsIndex++;
    }

    /**
     * neural network output is calculated here
     */
    outputs = process(inputs);

    /**
     * the outputs are used to control the plane
     */
    if(outputs[0] > 0.55){
        controlledPlane->turn(LEFT);
    }else if (outputs[0] < 0.45){
        controlledPlane->turn(RIGHT);
    }

    if(outputs[1] > 0.5){
        controlledPlane->shoot();
    }

    if(outputs[2] > 0.5) {
        controlledPlane->boost();
    }


}

NeuralController::~NeuralController() {
    delete inputs;


    GameEngine::removeObject(fieldOfView);

}


void NeuralController::randomize(double percent) {
    randomizeByPercent(percent);
}

