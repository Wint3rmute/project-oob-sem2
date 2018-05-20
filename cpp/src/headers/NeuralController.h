//
// Created by wint3rmute on 4/1/18.
//

#ifndef PROJECT_NEURALCONTROLLER_H
#define PROJECT_NEURALCONTROLLER_H


#include "NeuralNet.h"
#include "Controller.h"
#include "FieldOfView.h"
#include "../utils/constants.h"

/**
 * @brief Uses a neural network to move the plane around
 */
class NeuralController : public Controller, public NeuralNet {

    /**
     * @brief the input data for the neural net
     */
    double * inputs;
    /**
     * @brief the output data from the neural net
     *
     * this data steers the plane
     */
    double * outputs;

public:


    /**
     * @brief Creates a new, random neural controller
     */
    NeuralController(NetworkParams * params, Plane * plane, FieldOfView * fieldOfView);

    /**
     * @brief Creates a controller with weights copied from another network - the parent
     */
    NeuralController(NeuralController * parent, Plane * plane, FieldOfView * fieldOfView);

    /**
     * @brief @see Controller
     */
    void control();

    /**
     * Mutates a random percent of the network weights
     */
    void randomize(double percent);

    ~NeuralController();

};


#endif //PROJECT_NEURALCONTROLLER_H
