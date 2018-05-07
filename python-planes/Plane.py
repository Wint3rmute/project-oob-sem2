import constants
from pygame.locals import *  # Keys
import pygame
import pymunk  # For constructing the plane body
from pymunk.vec2d import Vec2d  # Vector calculations - needed for the plane to fly like a goddamn plane does
import math  # Żeby Pan Merdas był wesoły <3
from enum import Enum
import Bullet
import GameObject
import UtilClasses


class DIRECTION(Enum):
    LEFT = 1.
    RIGHT = -1


class Plane(GameObject.GameObject):

    def __init__(self,
                 start_x,
                 start_y,
                 angle,
                 ):

        self.body = UtilClasses.BetterBody(
            constants.PLANE_MASS,
            constants.PLANE_INERTIA,
            body_type=pymunk.Body.DYNAMIC,
            parent=self)

        self.body.center_of_gravity = constants.PLANE_GRAVITY_CENTER
        self.body.position = start_x, start_y
        self.shape = pymunk.Poly(self.body, constants.PLANE_VERTICES)
        self.shape.color = pygame.color.THECOLORS["white"]
        self.shape.collision_type = constants.PLANE_COLLISION_TYPE
        self.body.angle = angle  # works, no idea why

        self.speed = constants.PLANE_STARTING_SPEED
        self.ammo = constants.PLANE_STARTING_AMMO
        self.can_shoot = True

    def remove(self):
        pass

    def update(self):  # Called every frame
        # Engine
        self.speed -= math.sin(self.body.angle) * constants.PLANE_SPEED_CHANGE_RATE
        if self.speed < constants.PLANE_MIN_SPEED:
            self.speed = constants.PLANE_MIN_SPEED
        elif self.speed > constants.PLANE_MAX_SPEED:
            self.speed = constants.PLANE_MAX_SPEED
        self.body.position += Vec2d(self.speed, 0).rotated(self.body.angle)

        '''
        Bad practice hardcoded values <3
        '''
        if self.body.position[0] > constants.SCREEN_WIDTH + 20:
            self.body.position -= Vec2d(constants.SCREEN_WIDTH, 0)
        if self.body.position[1] > constants.SCREEN_HEIGHT + 20:
            self.body.position -= Vec2d(0, constants.SCREEN_HEIGHT + 20)
        if self.body.position[0] < -10:
            self.body.position += Vec2d(constants.SCREEN_WIDTH, 0)
        if self.body.position[1] < -10:
            self.body.position += Vec2d(0, constants.SCREEN_HEIGHT + 20)

        if self.ammo < constants.PLANE_STARTING_AMMO:
            self.ammo += 0.1
        else:
            self.can_shoot = True
        # print(self.ammo)

    def turn(self, direction):
        self.body.angle += direction.value * constants.PLANE_ROTATION_SPEED * self.speed

        if self.body.angle > 6.28318531:  # I am aware
            self.body.angle -= 6.28318531  # That this thing
        elif self.body.angle < 0.0:  # looks
            self.body.angle += 6.28318531  # really terrible

    def shoot(self):
        if self.ammo > 0 and self.can_shoot:
            Bullet.spawn_bullet(
                self
            )
            self.ammo -= 1
        else:
            self.can_shoot = False
