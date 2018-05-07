import math
import constants


def deg_2_rad(deg):
    return deg * constants.DEG_2_RAD


def rad_2_deg(rad):
    return rad * constants.RAD_2_DEG


def get_angle_sensor_value(plane_pos, object_pos):
    angle_plane = math.fmod(plane_pos.body.angle * constants.RAD_2_DEG, 360)
    angle_between = (plane_pos.body.position - object_pos.body.position).get_angle_degrees()
    if angle_between < 0:
        angle_between = angle_between + 360
        angle_plane = angle_plane + 360

    data_angle = angle_plane - angle_between + 180

    if data_angle >= 180:
        data_angle -= 360

    return data_angle / 360.0



def sigmoid(x, multiplier=1):
    """
    :param x: what to put into sigmoid function
    :param multiplier: the value that x will be multiplied by, default value is one
    :return: 1 / (1 - math.exp(-x * multiplier))
    """
    return 1 / (1 + math.exp(-x * multiplier))


