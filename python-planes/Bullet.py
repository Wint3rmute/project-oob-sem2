import constants
import UtilClasses
import pymunk
from pymunk.vec2d import Vec2d
import GameObject
import pygame


class Bullet(GameObject.GameObject):
    def __init__(self,
                 position,
                 angle,
                 ):
        self.body = UtilClasses.BetterBody(
            constants.BULLET_MASS,
            constants.BULLET_INERTIA,
            body_type=pymunk.Body.DYNAMIC,
            parent=self
        )
        self.body.position = position + Vec2d(40,5).rotated(angle)
        self.shape = pymunk.Circle(self.body, 5)
        self.shape.collision_type = constants.BULLET_COLLISION_TYPE
        self.movement_vector = Vec2d(constants.BULLET_SPEED, 0).rotated(angle)
        self.shape.color = pygame.color.THECOLORS["white"]

    def update(self):
        self.body.position += self.movement_vector
        if abs(self.body.position.x) > 2000 or abs(self.body.position.y) > 1000:
            self.game_engine.remove_object(self)
            pass

    def remove(self):
        pass


def spawn_bullet(plane_owner):
    bullet = Bullet(plane_owner.body.position, plane_owner.body.angle)
    plane_owner.game_engine.add_object(bullet)
