# TODO

## Controller
 - Controller base abstract class
    - `controll(Plane &plane, /* TODO referencja do listy obiektów z silnika gry */)`

 - Human controller -> Controller
    - controll uses inputs from keyboard

 - NNController -> Controller
    - controll works AI magically

## Class skill - a base class for each skill, eg. shoot, boost, EMP
 - `activate()` - fucking do this
 - `float cooldown` - cooldown time
 - `bool isOnCooldown()`
 - `startCooldown()`
 - `stopCooldown()`

## GameObject enhancements
 - property enum CollisionLoop

## Game engine
 - GameEngine class
    - Has a **dynamic list** of objects currently in scene - objectsList
    - addObject(GameObject & object)
    - removeOjbect(GameObject & object)
    - performStep() - simulates each object in objectsList
    - Has to count time in some way
    - Needs some gamestates eg blue_won, red_won, blue_crashed etc

 ## Plane enhancements
 
  - New skills
    -  Boost
    -  EMP
