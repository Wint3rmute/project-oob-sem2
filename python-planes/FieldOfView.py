import GameObject
import constants
import pymunk
import math
import Plane
import Bullet


def get_distance(position_a, position_b):
    return math.sqrt((position_a[0] - position_b[0])**2 + (position_a[1] - position_b[1])**2)


class FieldOfView(GameObject.GameObject):
    def __init__(self, plane_me):
        self.plane_me = plane_me
        self.cells = [None] * constants.VISUAL_CELLS_COUNT

        self.distances_to_bullets = [0] * constants.VISUAL_CELLS_COUNT
        self.distances_to_planes = [0] * constants.VISUAL_CELLS_COUNT

    def remove(self):
        pass

    def update(self):

        for i in range(constants.VISUAL_CELLS_COUNT):
            self.cells[i] = [
                self.plane_me.body.position.x + math.cos((360.0 / constants.VISUAL_CELLS_COUNT * i + self.plane_me.body.angle * constants.RAD_2_DEG) * constants.DEG_2_RAD) * constants.VISUAL_CELL_DISTANCE_FROM_PLANE,
                self.plane_me.body.position.x + math.sin((360.0 / constants.VISUAL_CELLS_COUNT * i + self.plane_me.body.angle * constants.RAD_2_DEG) * constants.DEG_2_RAD) * constants.VISUAL_CELL_DISTANCE_FROM_PLANE
            ]

            self.distances_to_bullets[i] = 0.
            self.distances_to_planes[i] = 0.

        smallest_distance_bullet, smallest_distance_plane = 10000, 10000
        best_visual_cell_number_bullet, best_visual_cell_number_plane = -1, -1

        for game_object in self.game_engine.game_objects:
            if game_object == self or game_object == self.plane_me:
                continue

            for i in range(len(self.cells)):
                temp_distance = get_distance(game_object.body.position, self.cells[i])
                if type(game_object) is Plane.Plane:
                    if temp_distance < smallest_distance_plane:
                        smallest_distance_plane = temp_distance
                        best_visual_cell_number_plane = i

                elif type(game_object) is Bullet.Bullet:
                    if temp_distance < smallest_distance_bullet:
                        smallest_distance_bullet = temp_distance
                        best_visual_cell_number_bullet = i

            if best_visual_cell_number_bullet != -1:
                self.distances_to_bullets[best_visual_cell_number_bullet] = smallest_distance_bullet

            if best_visual_cell_number_plane != -1:
                self.distances_to_planes[best_visual_cell_number_plane] = smallest_distance_plane
