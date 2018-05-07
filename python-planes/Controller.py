from abc import ABC, abstractmethod
from pygame.locals import *
from Plane import DIRECTION
import UtilFunctions
import random

class Controller(ABC):

    @abstractmethod
    def control(self):
        pass


class HumanController(Controller):

    def __init__(self, plane_me):
        self.plane_me = plane_me
        self.k_left = K_LEFT
        self.k_right = K_RIGHT
        self.k_shoot = K_SPACE

    def control(self):
        if self.game_engine.keys[self.k_left]:
            self.plane_me.turn(DIRECTION.LEFT)

        elif self.game_engine.keys[self.k_right]:
            self.plane_me.turn(DIRECTION.RIGHT)

        if self.game_engine.keys[self.k_shoot]:
            self.plane_me.shoot()

    def change_keys(self, key_left, key_right, key_shoot):
        self.k_left = key_left
        self.k_right = key_right
        self.k_shoot = key_shoot


class DummyController(Controller):  # Let's try using our template for som real stuff
    def __init__(self, plane_me):
        self.plane_me = plane_me

    def control(self):
        self.plane_me.turn(DIRECTION.LEFT)
        self.plane_me.shoot()  # Let me know if you can give that strategy a cool name


class FollowController(Controller):
    def __init__(self, plane_me, plane_enemy, difficulty):
        self.plane_me = plane_me
        self.plane_enemy = plane_enemy
        self.difficulty = difficulty

    def control(self):
        angle_between = UtilFunctions.get_angle_sensor_value(self.plane_me, self.plane_enemy)

        if random.randint(0, 100) < self.difficulty:
            return

        if angle_between > 0:
            self.plane_me.turn(DIRECTION.RIGHT)
        else:
            self.plane_me.turn(DIRECTION.LEFT)

        if abs(angle_between) < 10 and self.plane_me.body.position.get_distance(self.plane_enemy.body.position) < 500:
            self.plane_me.shoot()
