//
// Created by wint3rmute on 3/6/18.
//

#ifndef PROJECT_CONSTANTS_H
#define PROJECT_CONSTANTS_H

/*
 * Game engine related
 */
#define GAME_WINDOW_HEIGHT 1000
#define GAME_WINDOW_WIDTH 1000
#define FRAME_TIME (1.0/60.0)
#define TELEPORTATION_TRIGGER_OFFSET 20
#define BACKGROUND_COLOR sf::Color(56,56,56)

/*
 * Plane object related
 */
#define PLANE_COLLIDER_SIZE 10
#define PLANE_SPEED 2
#define ACCELERATION_MULTIPLIER 0.03
#define MAX_SPEED 7
#define MIN_SPEED 2
#define ROTATION_SPEED 1


/*
 * Bullet object related
 */
#define BULLET_SPEED 10
#define BULLET_SIZE 3.f
#define BULLET_SPAWN_BEFORE_DISTANCE 25

/*
 * Gun object related
 */
#define PISTOL_AMMO 15
#define PISTOL_COOLDOWN_TIME 3.0f
#define PISTOL_SHOOT_RATE 0.07f

/*
 * FieldOfView object related
 */
#define VISUAL_CELLS_COUNT 30
#define VISUAL_CELL_SIZE 4
#define VISUAL_CELL_DISTANCE_FROM_PLANE 30

/*
 * Physical & mathematical constants
 */
#define DEG_2_RAD 0.0174532925


#endif //PROJECT_CONSTANTS_H
