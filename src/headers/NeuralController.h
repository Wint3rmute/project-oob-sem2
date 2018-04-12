//
// Created by wint3rmute on 4/1/18.
//

#ifndef PROJECT_NEURALCONTROLLER_H
#define PROJECT_NEURALCONTROLLER_H


#include "NeuralNet.h"
#include "Controller.h"
#include "FieldOfView.h"
#include "../utils/constants.h"

class NeuralController : public Controller, NeuralNet {

    FieldOfView * fieldOfView;

    double * inputs;
    double * outputs;

public:
    NeuralController(NetworkParams * params, Plane * plane, FieldOfView * fieldOfView);
    NeuralController(NeuralController * parent, Plane * plane, FieldOfView * fieldOfView);
    void control();
    void randomize(double percent);

    ~NeuralController();

};


#endif //PROJECT_NEURALCONTROLLER_H
