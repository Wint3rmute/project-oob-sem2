"""
Some smart stuff will be written here some day
"""
from enum import Enum

import pygame
from pygame.locals import *
import pymunk
import pymunk.pygame_util

import constants
import Plane
#import controllers
import random
import os
import datetime
import Controller
import Bullet
import utils
import sys
import FieldOfView


class GameState(Enum):
    running = 0
    plane_1_won = 1
    plane_2_won = 2
    plane_1_crashed = 4
    plane_2_crashed = 5
    collision = 6
    time_over = 7
    quit = 8


# noinspection PyUnusedLocal
class GameEngine:
    def __init__(self):
        """
        Constructor only loads the pygame module,
        then sets the rest of class attributes to None.
        Other tasks such as creating the game window
        are moved to create_basic_game_components method,
        since they will be reused when launching the game
        in different modes (train/vs/whatever else may come)
        """
        # Game engine related
        self.screen = None
        self.clock = None
        self.space = None
        self.draw_options = None
        self.font = None  # But do we really need a font..?
        self.keys = None

        # Simulation related
        self.game_objects = []
        self.game_objects_remove_queue = []

        self.controllers = []
        self.controllers_remove_queue = []

        self.game_state = None
        self.game_time = None
        self._fps = constants.FRAMERATE
        self._dt = 1 / self._fps
        self.start_time = None
        self._visible = None

        """
        Those two fields are customisable by the user, by default set to an empty function, which does nothing
        """
        self.before_frame_function = self.__empty_function
        self.after_frame_function = self.__empty_function

    def set_visibility(self, value):
        """
        :param value: boolean - should the game window be visible or not?
        """
        self._visible = value

    def add_object(self, new_object):
        #if new_object not in self.game_objects:
        new_object.game_engine = self  # Giving the object a reference to the Game Engine
        self.game_objects.append(new_object)
        if type(new_object) is FieldOfView.FieldOfView:
            return

        self.space.add(new_object.shape, new_object.body)

    def remove_object(self, object_to_remove):
        """
        Objects are not removed instantly, because it could do bad stuff to objects linked with them,

        They are pushed into a queue, and removed after each frame
        """
        if object_to_remove not in self.game_objects_remove_queue:
            self.game_objects_remove_queue.append(object_to_remove)

    def _clear_remove_objects_queue(self):
        while len(self.game_objects_remove_queue) != 0:
            object_to_remove = self.game_objects_remove_queue[0]
            self.game_objects.remove(object_to_remove)
            self.game_objects_remove_queue.remove(object_to_remove)
            self.space.remove(object_to_remove.shape, object_to_remove.body)
            del object_to_remove
            #print('REMOVING!')

    def add_controller(self, new_controller):
        new_controller.game_engine = self  # Giving the object a reference to the Game Engine
        self.controllers.append(new_controller)

    def remove_controller(self, controller_to_remove):
        """
        Objects are not removed instantly, because it could do bad stuff to objects linked with them,

        They are pushed into a queue, and removed after each frame
        """
        if controller_to_remove not in self.controllers_remove_queue:
            self.controllers_remove_queue.append(controller_to_remove)

    def _clear_remove_controllers_queue(self):
        while len(self.controllers_remove_queue) != 0:
            object_to_remove = self.game_objects_remove_queue[0]
            self.game_objects.remove(object_to_remove)
            self.game_objects_remove_queue.remove(object_to_remove)
            del object_to_remove

    def planes_collision(self, arbiter, space, data):
        print("planes collision!")

        plane1, plane2 = arbiter.shapes

        plane1 = plane1.body.parent
        plane2 = plane2.body.parent

        self.remove_object(plane1)
        self.remove_object(plane2)

        return False

    def plane_bullet_collision(self, arbiter, space, data):
        print("bullet hit")
        plane1, plane2 = arbiter.shapes

        plane1 = plane1.body.parent
        plane2 = plane2.body.parent

        self.remove_object(plane1)
        self.remove_object(plane2)
        return False

    def init_collisions(self):

        bullet_hit_plane = self.space.add_collision_handler(  # Plane a scores
            constants.PLANE_COLLISION_TYPE, constants.BULLET_COLLISION_TYPE
        )
        bullet_hit_plane.pre_solve = self.plane_bullet_collision

        planes_collision = self.space.add_collision_handler(  # Plane b scores
            constants.PLANE_COLLISION_TYPE, constants.PLANE_COLLISION_TYPE
        )
        planes_collision.pre_solve = self.planes_collision


    def create_basic_game_components(self, is_visible=True):
        """
        iiInitializes things that are needed to run psychics simulation and graphic engine
        Makes a basic pygame window and connects it with the pymunk physic engine (if visible set to True)

        :param is_visible: if visible, you can see what's happening. If not, the simulation runs in turbo mode, invisible
        """

        self.clock = pygame.time.Clock()
        self.space = pymunk.Space()
        self.space.gravity = 0, constants.GRAVITY_FORCE
        self.game_time = 0.
        self._visible = is_visible

        self.init_collisions()

        pygame.init()
        if is_visible:
            self.screen = pygame.display.set_mode((constants.SCREEN_WIDTH, constants.SCREEN_HEIGHT))
            self.draw_options = pymunk.pygame_util.DrawOptions(self.screen)  # connecting the physics to graphics
            self.font = pygame.font.SysFont("Arial", 16)
        else:
            print("running in invisible-turbo-speed-mode")

        """
        safety check if the networks saving and loading directory exists
        """
        current_dir = os.getcwd()
        folder_dir = os.path.join(current_dir, r'saved_networks')
        if not os.path.exists(folder_dir):
            os.makedirs(folder_dir)

        # TODO: use this somehow
        self.start_time = datetime.datetime.now()

    def simulation_step(self):
        """
        does the physics simulation and screen drawing after our game has finished input processing and
        other operations
        """

        for game_object in self.game_objects:
            game_object.update()
        for controller in self.controllers:
            controller.control()

        if self._visible:
            # Clear screen
            self.screen.fill(pygame.color.Color(47, 52, 63, 100))#THECOLORS["ff0000"])

            # Draw stuff
            self.space.debug_draw(self.draw_options)
            # draw(screen, space)

            pygame.display.flip()
            self.clock.tick(self._fps)

        self._clear_remove_controllers_queue()
        self._clear_remove_objects_queue()
        # Update physics
        self.space.step(self._dt)
        self.game_time += self._dt

        # pygame.display.set_caption("Time: " + str(round(self.game_time, 1)))
        # The line above can break the whole UI on linux.. for no reason

    @staticmethod
    def get_random_plane_position():  # TODO: make this responsive to screen size
        return random.randrange(1000) + 100, random.randrange(600) + 100

    def play(self):
        self.game_state = GameState.running  # This enum will determine whether the game is over and show it's result

        # Here the game starts
        while self.game_state == GameState.running:

            for event in pygame.event.get():  # event loop
                if event.type == QUIT:
                    self.game_state = GameState.quit

            self.keys = pygame.key.get_pressed()
            self.simulation_step()  # Draw the simulation # THIS HAS BUGZ

    def __empty_function(self):
        """
        Empty function used by the GameEngine as function_before_frame and function_after_frame by default
        """
        pass


def help_message():
    print("""
    
    Plane Experiment
    
    Usage:
    
        --help: print this help message
        --play-2: 2 players, both human, one keyboard
        
        --play-ai-1: play with AI, simple difficulty level
        --play-ai-2: play with AI, medium difficulty level
        --play-ai-3: play with AI, terminator difficulty level
    """)

if __name__ == "__main__":
    if(len(sys.argv) == 1):
        print("wrong usage!")
        help_message()
        exit(1)

    arg = str(sys.argv[1])


    my_game = GameEngine()
    my_game.create_basic_game_components()

    if arg == "--play-2":
        plane = Plane.Plane(200, 600, 0)
        contr1 = Controller.HumanController(plane)
        plane2 = Plane.Plane(900, 600, 3.14)

        contr2 = Controller.HumanController(plane2)
        contr2.change_keys(
            K_a,
            K_d,
            K_w
        )

        my_game.add_object(plane2)
        my_game.add_controller(contr1)
        my_game.add_controller(contr2)
        my_game.add_object(plane)

    elif arg == "--play-ai-1":
        plane = Plane.Plane(200, 600, 0)
        contr1 = Controller.HumanController(plane)
        plane2 = Plane.Plane(900, 600, 3.14)

        contr2 = Controller.FollowController(plane2, plane, 70)

        my_game.add_object(plane2)
        my_game.add_controller(contr1)
        my_game.add_controller(contr2)
        my_game.add_object(plane)

    elif arg == "--play-ai-2":
        plane = Plane.Plane(200, 600, 0)
        contr1 = Controller.HumanController(plane)
        plane2 = Plane.Plane(900, 600, 3.14)

        contr2 = Controller.FollowController(plane2, plane, 50)

        my_game.add_object(plane2)
        my_game.add_controller(contr1)
        my_game.add_controller(contr2)
        my_game.add_object(plane)

    elif arg == "--play-ai-3":
        plane = Plane.Plane(200, 600, 0)
        contr1 = Controller.HumanController(plane)
        plane2 = Plane.Plane(900, 600, 3.14)

        contr2 = Controller.FollowController(plane2, plane, 10)

        my_game.add_object(plane2)
        my_game.add_controller(contr1)
        my_game.add_controller(contr2)
        my_game.add_object(plane)

    else:
        help_message()
        exit(1)

    my_game.play()
