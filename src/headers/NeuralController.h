//
// Created by wint3rmute on 4/1/18.
//

#ifndef PROJECT_NEURALCONTROLLER_H
#define PROJECT_NEURALCONTROLLER_H


#include "NeuralNet.h"
#include "Controller.h"
#include "FieldOfView.h"
#include "../utils/constants.h"

class NeuralController : public Controller, public NeuralNet {


    double * inputs;
    double * outputs;

public:


    /*
     * This creates a new, random neural network
     */
    NeuralController(NetworkParams * params, Plane * plane, FieldOfView * fieldOfView);

    /*
     * This creates a controller with weights copied from another network - the parent
     */
    NeuralController(NeuralController * parent, Plane * plane, FieldOfView * fieldOfView);
    void control();

    /*
     * Mutates a random percent of the network weights
     */
    void randomize(double percent);

    ~NeuralController();

};


#endif //PROJECT_NEURALCONTROLLER_H
