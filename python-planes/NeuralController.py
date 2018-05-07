import Controller
from Plane import DIRECTION
import Bullet
import numpy as np
import random
import UtilFunctions
from constants import *


class NeuralController(Controller.Controller):

    def __init__(self, plane_me, field_of_view):
        """
        Tutaj tworzenie tej tablicy dwuwymiarowych tablic
        """
        self.weights_count = 0

        self.plane_me = plane_me
        self.field_of_view = field_of_view
        self.NETWORK_PARAMETERS = NETWORK_PARAMETERS
        self.weights = np.ndarray(shape=[len(NETWORK_PARAMETERS) - 1], dtype=np.ndarray)
        self.perceptron_values = np.ndarray([len(NETWORK_PARAMETERS)], dtype=np.ndarray)

        for i in range(len(NETWORK_PARAMETERS) - 1):
            self.weights[i] = (np.random.uniform(-1, 1, (NETWORK_PARAMETERS[i], NETWORK_PARAMETERS[i + 1])))
            self.weights_count += NETWORK_PARAMETERS[i] * NETWORK_PARAMETERS[i + 1]

        for i in range(len(NETWORK_PARAMETERS)):
            self.perceptron_values[i] = np.zeros([NETWORK_PARAMETERS[i]], dtype=float)

    @staticmethod
    def normalize(current_value, maximum_value):
        return 2 * current_value / maximum_value - 1  # try to simplify this: (value-(max/2))/(max/2)

    def control(self):

        # bullets input left to do
        """for i in range(7,28):
            self.perceptron_values[0][i] = sigmoid(bullets[i-7].bullet_body.position[0])
        for i in range(27, 48):
            self.perceptron_values[0][i] = sigmoid(bullets[i-27].bullet_body.position[1])
        """
        for i in range(len(self.NETWORK_PARAMETERS) - 1):
            self.perceptron_values[i + 1] = np.dot(self.perceptron_values[i], self.weights[i])
            for j in range(len(self.perceptron_values[i+1])):  # This cannot be the most efficient way to do this
                self.perceptron_values[i+1][j] = UtilFunctions.sigmoid(self.perceptron_values[i+1][j])

        if self.perceptron_values[-1][0] > 0.5:
            self.plane_me.turn(DIRECTION.LEFT)
        else:
            self.plane_me.turn(DIRECTION.RIGHT)

        if self.perceptron_values[-1][1] > 0.5:
            self.plane_me.shoot()

        print(self.perceptron_values[-1])

    def mutate_by_percent(self, percent):
        mutations_count = int(self.weights_count * percent)
        mutated_cells = []
        while len(set(mutated_cells)) < mutations_count:  # set is a collection of unique elements
            current_mutated_cell = self.mutate_random()
            mutated_cells.append(current_mutated_cell)
            #print(len(set(mutated_cells)))

    def mutate_random(self):
        mutation_layer = random.randrange(len(self.weights))
        mutation_row = random.randrange(len(self.weights[mutation_layer]))
        mutation_column = random.randrange(len(self.weights[mutation_layer][mutation_row]))
        self.weights[mutation_layer][mutation_row][mutation_column] = random.uniform(-1,1)
        return mutation_layer, mutation_row, mutation_column

    def load_from_file(self, file_name):
        file = open(file_name, 'r')


